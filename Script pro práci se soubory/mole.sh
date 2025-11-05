#Funkce, která vypíše log ke scriptu
usage(){
	echo Návod k použití scriptu mole.sh:
	echo "	název_souboru -> soubor se otevře"
	echo "	-h -> vypíše se tento návod"
	echo "	-g [skupina] název_souboru -> soubor se otevře a přiřadí do skupiny"
	echo "	-m -> otevře se nejčastěji otevřený soubor"
	echo "	-m cesta -> vypíše se seznam otevřených souborů v daném adresáři"
	echo "	list -> vypíše soubory, které dříve uživatel přes script otevřel"
}

cnt="pokracovat"

#Kontrola  zda jsou zadány nějaké argumenty
if [ $# -eq 0 ]; then
	usage
	cnt="konec"
fi

touch MOLE_RC

#CASE na zíkání -x
while getopts :g:m o
do	case "$o" in
	g)	
		if [ $# -eq 2 ]; then
			usage
			cnt="konec"
		else
			if grep -q "^$3;" MOLE_RC; then
				# uložení řádku s hledaným názvem do proměnné
				matching_line=$(grep "$3;" MOLE_RC)

				# oddělení části řádku s hodnotou a uložení do proměnné
				value=$(echo "$matching_line" | cut -d ';' -f 5)

				# zvýšení hodnoty o jedna
				num=$((value + 1))
				
	  			sed -i "s/^$3;.*/$3;$(date '+%Y-%m-%d %H:%M:%S');$USER;$2;$num/" MOLE_RC
			else
	  			echo "$3;$(date '+%Y-%m-%d %H:%M:%S');$USER;$2;1" >> MOLE_RC
			fi
		
			nano $3
		
			cnt="konec"
		fi
		;;
	m)
		if [ $# -eq 1 ]; then
			max=$(sort -t ';' -k 5 -nr MOLE_RC | head -1)
			nazev=$(echo "$max" | cut -d ';' -f 1)
			value=$(echo "$max" | cut -d ';' -f 5)
			new_value=$((value + 1))
			group=$(echo "$max" | cut -d ';' -f 4)
			
			sed -i "/^$nazev;/c$nazev;$(date '+%Y-%m-%d %H:%M:%S');$USER;$group;$new_value" MOLE_RC

			nano $nazev

			cnt="konec"
		else
			matching_line=$(grep "$2" MOLE_RC)
			if [ -n "$matching_line" ]; then
				nazev=$(echo "$matching_line" | cut -d ';' -f 1)
				value=$(echo "$matching_line" | cut -d ';' -f 5)
				new_value=$((value + 1))
				group=$(echo "$matching_line" | cut -d ';' -f 4)
				
				sed -i "/^$nazev;/c$nazev;$(date '+%Y-%m-%d %H:%M:%S');$USER;$group;$new_value" MOLE_RC
				
				nano $nazev
			fi
			cnt="konec"
		fi
		;;
	*)	
		usage
		cnt="konec"
		;;
	
	esac
done

if [ $cnt = "pokracovat" ]; then
	#CASE na získání argumentů
	case "$1" in
		list)
			if [ $# -eq 1 ]; then
				cat MOLE_RC
			else
				grep $2 MOLE_RC
			fi
			;;
		secret-log)
			if [ $# -eq 1 ]; then
				cat MOLE_RC
			fi
			;;
		*)
			if grep -q "^$1;" MOLE_RC; then
				# uložení řádku s hledaným názvem do proměnné
				matching_line=$(grep "^$1;" MOLE_RC)

				# oddělení části řádku s hodnotou a uložení do proměnné
				value=$(echo "$matching_line" | cut -d ';' -f 5)

				# zvýšení hodnoty o jedna
				new_value=$((value + 1))
				
				# uložení řádku s hledaným názvem do proměnné
				line=$(grep "^$1;" MOLE_RC)

				# oddělení části řádku s hodnotou a uložení do proměnné
				group=$(echo "$line" | cut -d ';' -f 4)
				
				sed -i "/^$1;/c$1;$(date '+%Y-%m-%d %H:%M:%S');$USER;$group;$new_value" MOLE_RC
			else
	  			echo "$1;$(date '+%Y-%m-%d %H:%M:%S');$USER;;1" >> MOLE_RC
			fi

			nano $1
			;;
	esac
fi
