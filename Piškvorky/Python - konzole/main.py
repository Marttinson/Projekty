#Vytvoření a naplnění proměnné, ve které je uložené hrací pole a postupně se uloží postup hrou
hraci_pole = []
for i in range(10):
  temp = []
  for a in range(10):
    temp.append(" ")
  hraci_pole.append(temp)

#Doplnění os souřadnic
for i in range(1, 10, 1):
  hraci_pole[0][i] = i
  hraci_pole[i][0] = i

#Vstup a jeho kontrola pro zadání počtu na výhru
zadano = False
while not(zadano):
  try:
    pocet_pro_vyhru = int(input("Zadejte na kolik chcete hrat: "))
    zadano = True
  except ValueError:
    print("Neplatna hodnota\n")

#Tady začíná herní cyklus, který běží po celou dobu co běží samotná hra
konec = False
pocet_kol = 0
while not(konec):
  vyhrano = ""
  #Určení který hráč je na řadě, pomocí čísla kola
  if pocet_kol % 2 == 1:
    print("Na rade je hrac s krizky")
    znak = "X"
  else:
    print("Na rade je hrac s kolecky")
    znak = "O"

  #Výpis hracího pole
  for i in range(10):
    for a in range(10):
      print(hraci_pole[i][a], end="")
      print("|", end="")
    print(end="\n")
  
  #Vstupy a jejich kontrola, pro zadání souřadnic
  try:
    souradniceX = int(input("Zadej souradnice na ose X: "))
  except ValueError:
    print("Neplatna hodnota souradnic\n")
    continue

  if 0 < souradniceX < 10:
    pass
  else:
    print("Neplatna hodnota souradnic\n")
    continue

  try:
    souradniceY = int(input("Zadej souradnice na ose Y: "))
  except ValueError:
    print("Neplatna hodnota souradnic\n")
    continue

  if 0 < souradniceY < 10:
    pass
  else:
    print("Neplatna hodnota sourandic\n")
    continue

  #Kontrola, zda je pole volné či nikoliv
  if hraci_pole[souradniceY][souradniceX] == " ":
    hraci_pole[souradniceY][souradniceX] = znak
  else:
    print("Pole je obsazeno\n")
    continue

  #Kontrola výhry na vodorovné ose
  je_tak = True
  vitez = 1
  vodorovneX = souradniceX
  vodorovneY = souradniceY
  while je_tak:
    vodorovneX += 1
    if vodorovneX <= 9:
      if hraci_pole[vodorovneY][vodorovneX] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False
    
  je_tak = True
  vodorovneX = souradniceX
  vodorovneY = souradniceY
  while je_tak:
    vodorovneX -= 1
    if vodorovneX >= 1:
      if hraci_pole[vodorovneY][vodorovneX] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False

  if vitez >= pocet_pro_vyhru:
    vyhrano = znak

  #Kontrola výhry na svislé ose
  vitez = 1
  je_tak = True
  vertikalniX = souradniceX
  vertikalniY = souradniceY

  while je_tak:
    vertikalniY += 1
    if vertikalniY <= 9:
      if hraci_pole[vertikalniY][vertikalniX] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False
    
  je_tak = True
  vertikalniX = souradniceX
  vertikalniY = souradniceY
  while je_tak:
    vertikalniY -= 1
    if vertikalniY >= 1:
      if hraci_pole[vertikalniY][vertikalniX] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False

  if vitez >= pocet_pro_vyhru:
    vyhrano = znak

  #Kontrola výhry na šíkmé ose
  je_tak = True
  sikmo1X = souradniceX
  sikmo1Y = souradniceY
  while je_tak:
    sikmo1X += 1
    sikmo1Y -= 1
    if sikmo1Y >= 1 and sikmo1X <= 10:
      if hraci_pole[sikmo1Y][sikmo1X] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False

  if vitez >= pocet_pro_vyhru:
    vyhrano = znak

  je_tak = True
  sikmo1X = souradniceX
  sikmo1Y = souradniceY
  while je_tak:
    sikmo1X -= 1
    sikmo1Y += 1
    if sikmo1Y >= 1 and sikmo1X <= 10:
      if hraci_pole[sikmo1Y][sikmo1X] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False

  if vitez >= pocet_pro_vyhru:
    vyhrano = znak

  #Kontrola výhry na druhé šikmé ose
  je_tak = True
  sikmo2X = souradniceX
  sikmo2Y = souradniceY
  while je_tak:
    sikmo2X -= 1
    sikmo2Y -= 1
    if sikmo2Y >= 1 and sikmo2X >= 1:
      if hraci_pole[sikmo2Y][sikmo2X] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False

  if vitez >= pocet_pro_vyhru:
    vyhrano = znak

  je_tak = True
  sikmo2X = souradniceX
  sikmo2Y = souradniceY
  while je_tak:
    sikmo2X += 1
    sikmo2Y += 1
    if sikmo2Y <= 10 and sikmo2X <= 10:
      if hraci_pole[sikmo2Y][sikmo2X] == znak:
        vitez += 1
      else:
        je_tak = False
    else:
      je_tak = False

  if vitez >= pocet_pro_vyhru:
    vyhrano = znak

  #Tady se výhra vypíše, pokud proběhla
  if vyhrano == "X":
    for i in range(10):
      for a in range(10):
        print(hraci_pole[i][a], end="")
        print("|", end="")
      print(end="\n")
    print("Vyhral hrac s krizky")
    konec = True
  elif vyhrano == "O":
    for i in range(10):
      for a in range(10):
        print(hraci_pole[i][a], end="")
        print("|", end="")
      print(end="\n")
    print("Vyhral hrac s kolecky")
    konec = True
  elif pocet_kol == 80:
    for i in range(10):
      for a in range(10):
        print(hraci_pole[i][a], end="")
        print("|", end="")
      print(end="\n")
    print("Remiza")
    konec = True
  else:
    pass

  #Na konci každého kola se počet kol zvýší o 1
  pocet_kol += 1