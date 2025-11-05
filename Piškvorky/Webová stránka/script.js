let tabulka = document.getElementById("tabulka");
let cislo=0;
let hraci_pole = []
let sloupce = []
let pocetpoli= prompt("Zadejte počet polí", "16");;
let pocetkol= prompt("Zadejte vytezných kol", "4");
for(let i=0;i<pocetpoli;i++){
  sloupce = []
  let tr = document.createElement("tr");
  tabulka.appendChild(tr);
  for(let d=0;d<pocetpoli;d++){
    sloupce.push("")
    let td = document.createElement("td");
    let textI = i.toString()
    if(textI.length == 1){
      textI = "0" + textI;
    }
    let textD = d.toString()
    if(textD.length == 1){
      textD = "0" + textD;
    }
    cislo= textI + textD;
    td.id = cislo;
    td.setAttribute("onclick","hra("+cislo+", "+textI.toString()+", "+textD.toString()+")");
    if(d%2 ==1 && i%2==1){
      td.classList.add("a");
    }
    if(d%2==0 && i%2==0){
      td.classList.add("a");
    }
    tr.appendChild(td);
  }
  hraci_pole.push(sloupce)
}
function getRed(id){
  let element = document.getElementById(id);
  element.classList.add("red");
  setTimeout(function(){element.classList.remove("red")},2000);
}
let dohrano = false;
let znak = ""
let pocet_kol = 0
let id= ""
let x = 0
let y = 0
function hra(_id, _textI, _textD){
  _textI = _textI.toString();
  if(_textI.length == 1){
    _textI = "0" + _textI;
  }
  _textD = _textD.toString();
  if(_textD.length == 1){
    _textD = "0" + _textD;
  }
  id = _textI + _textD;

  if (pocet_kol % 2 == 1){
    znak = "X"
  }
  else{
    znak = "O"
  }
  
  if (document.getElementById(id).textContent != ""){
    getRed(id);
    pocet_kol = pocet_kol - 1;
  }
  else{
    document.getElementById(id).textContent=znak;
    /*
    x = parseInt(id[0]);
    y = parseInt(id[1]);
    */
    x = parseInt(_textI);
    y = parseInt(_textD);
    hraci_pole[x][y] = znak;
  }

  if(dohrano == false){
    potvrzeniVyhryVodorovne(y, x, znak);
    potvrzeniVyhryVertikalne(y, x, znak);
    potvrzeniVyhrySikmo1(y, x, znak);
    potvrzeniVyhrySikmo2(y, x, znak);
  }
  pocet_kol = pocet_kol + 1;
}

let vyhrana_policka = []
let souradnice = []
function potvrzeniVyhryVodorovne(x, y, znak){
  vyhrana_policka = []
  let vitez = 1;
  let vodorovneY = y;
  let vodorovneX = x;
  let je_tak = true;
  while (je_tak == true){
    vyhrana_policka.push(vodorovneX);
    vodorovneX = vodorovneX + 1;
    if (vodorovneX < pocetpoli){
      if (hraci_pole[vodorovneY][vodorovneX] == znak){
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  je_tak = true
  vodorovneX = x;
  while (je_tak == true){
    vodorovneX = vodorovneX - 1;
    if (vodorovneX >= 0){
      if (hraci_pole[vodorovneY][vodorovneX] == znak){
        vyhrana_policka.push(vodorovneX);
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  for(let i = 0; i < vyhrana_policka.length; i++){
    let pomoc = vyhrana_policka[i].toString();
    if(pomoc.length == 1){
      vyhrana_policka[i] = "0" + vyhrana_policka[i];
    }
  }
  if(y.toString().length == 1){
    y = "0" + y;
  }

  if(vitez >= pocetkol){
    dohrano = true;
    for(let i = 0; i < vitez; i++){
      souradnice.push(y + vyhrana_policka[i].toString());
      let ctverec = document.getElementById(souradnice[i]);
      ctverec.classList.add("green");
      setTimeout(function(){location.reload();},5000)
    }
  }
}

function potvrzeniVyhryVertikalne(x, y, znak){
  vyhrana_policka = []
  let vitez = 1;
  let vertikalneY = y;
  let vertikalneX = x;
  let je_tak = true;
  while (je_tak == true){
      vyhrana_policka.push(vertikalneY);
      vertikalneY = vertikalneY + 1;
      if(vertikalneY < pocetpoli){
      if (hraci_pole[vertikalneY][vertikalneX] == znak){
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  je_tak = true
  vertikalneY = y;
  while (je_tak == true){
    vertikalneY = vertikalneY - 1;
    if (vertikalneY >= 0){
      if (hraci_pole[vertikalneY][vertikalneX] == znak){
        vyhrana_policka.push(vertikalneY);
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  for(let i = 0; i < vyhrana_policka.length; i++){
    let pomoc = vyhrana_policka[i].toString();
    if(pomoc.length == 1){
      vyhrana_policka[i] = "0" + vyhrana_policka[i];
    }
  }
  if(x.toString().length == 1){
    x = "0" + x;
  }

  if(vitez >= pocetkol){
    dohrano = true;
    for(let i = 0; i < vitez; i++){
      souradnice.push(vyhrana_policka[i].toString() + x.toString());
      let ctverec = document.getElementById(souradnice[i]);
      ctverec.classList.add("green");
      setTimeout(function(){location.reload();},3000)
    }
  }
}

function potvrzeniVyhrySikmo1(x, y, znak){
  vyhrana_polickaX = []
  vyhrana_polickaY = []
  let vitez = 1;
  let sikmoY = y;
  let sikmoX = x;
  let je_tak = true;
  
  while (je_tak == true){
      vyhrana_polickaY.push(sikmoY);
      vyhrana_polickaX.push(sikmoX);
      sikmoX = sikmoX + 1;
      sikmoY = sikmoY - 1;
      if(sikmoY >= 0 && sikmoX <= pocetpoli){
      if (hraci_pole[sikmoY][sikmoX] == znak){
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  je_tak = true
  sikmoX = x;
  sikmoY = y;
  while (je_tak == true){
    sikmoX = sikmoX - 1;
    sikmoY = sikmoY + 1;
    if (sikmoX >= 0 && sikmoY < pocetpoli){
      if (hraci_pole[sikmoY][sikmoX] == znak){
        vyhrana_polickaY.push(sikmoY);
        vyhrana_polickaX.push(sikmoX);
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  for(let i = 0; i < vyhrana_polickaX.length; i++){
    let pomoc = vyhrana_polickaX[i].toString();
    if(pomoc.length == 1){
      vyhrana_polickaX[i] = "0" + vyhrana_polickaX[i];
    }
  }
  for(let i = 0; i < vyhrana_polickaY.length; i++){
    let pomoc = vyhrana_polickaY[i].toString();
    if(pomoc.length == 1){
      vyhrana_polickaY[i] = "0" + vyhrana_polickaY[i];
    }
  }

  if(vitez >= pocetkol){
    dohrano = true;
    for(let i = 0; i < vitez; i++){
      souradnice.push(vyhrana_polickaY[i].toString() + vyhrana_polickaX[i].toString());
      let ctverec = document.getElementById(souradnice[i]);
      ctverec.classList.add("green");
      setTimeout(function(){location.reload();},3000)
    }
  }
}

function potvrzeniVyhrySikmo2(x, y, znak){
  vyhrana_polickaX = []
  vyhrana_polickaY = []
  let vitez = 1;
  let sikmoY = y;
  let sikmoX = x;
  let je_tak = true;
  
  while (je_tak == true){
      vyhrana_polickaY.push(sikmoY);
      vyhrana_polickaX.push(sikmoX);
      sikmoX = sikmoX - 1;
      sikmoY = sikmoY - 1;
      if(sikmoY >= 0 && sikmoX >= 0){
      if (hraci_pole[sikmoY][sikmoX] == znak){
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  je_tak = true
  sikmoX = x;
  sikmoY = y;
  while (je_tak == true){
    sikmoX = sikmoX + 1;
    sikmoY = sikmoY + 1;
    if (sikmoX <= pocetpoli && sikmoY < pocetpoli){
      if (hraci_pole[sikmoY][sikmoX] == znak){
        vyhrana_polickaY.push(sikmoY);
        vyhrana_polickaX.push(sikmoX);
        vitez = vitez + 1;
      }
      else{
        je_tak = false;
      }
    }
    else{
      je_tak = false;
    }
  }

  for(let i = 0; i < vyhrana_polickaX.length; i++){
    let pomoc = vyhrana_polickaX[i].toString();
    if(pomoc.length == 1){
      vyhrana_polickaX[i] = "0" + vyhrana_polickaX[i];
    }
  }
  for(let i = 0; i < vyhrana_polickaY.length; i++){
    let pomoc = vyhrana_polickaY[i].toString();
    if(pomoc.length == 1){
      vyhrana_polickaY[i] = "0" + vyhrana_polickaY[i];
    }
  }

  if(vitez >= pocetkol){
    dohrano = true;
    for(let i = 0; i < vitez; i++){
      souradnice.push(vyhrana_polickaY[i].toString() + vyhrana_polickaX[i].toString());
      let ctverec = document.getElementById(souradnice[i]);
      ctverec.classList.add("green");
      setTimeout(function(){location.reload();},3000)
    }
  }
}