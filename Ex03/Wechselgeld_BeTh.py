
import sys
import argparse
import string
import copy
_verbosity=5

def main():
    global _verbosity
    stueck=[]
    einh=[]
## Comandline optionen verarbeiten
    parser=argparse.ArgumentParser(description="Loest das Wechselgeldproblem.")
    parser.add_argument("-v", nargs='?', type=int , help="Setzt den Verbositylevel zur angegebenen Zahl", default=5, const=6)
    parser.add_argument("Wechselgeld" ,  help="Gibt das Geld an, das herausgegeben wird. Einheiten können optional NACHGESTELLT angegeben werden, wobei mit der groessten Einheit begonnen werden muss!", default=0)
    parser.add_argument("-s","--stueck", nargs='+', type=float, help="Manuelle Eingabe der Stueckelung. Nur ganze Zahlen sind erlaubt")
    parser.add_argument("-w","--waehrung", nargs='+', help="Gibt das/die Waehrungssymbol(e) an, beginnend mit dem kleinsten!")
    parser.add_argument("-u","--umrechnung", nargs='*', type=float, default=1, help="Gibt die Gewichtung der einzelnen Waehrungssymbole an. Beispiel Euro: Wurden die Waehrungssymbole als E c eingegeben, so ist hier 1 0.01 einzugeben. Für die Waehrungssymbole c E reicht 0.01")
    parser.add_argument("-d","--d_stueck", nargs='?', choices=["e","euro","p10", "p100", "p10*", "p100*", "T"], help="Waehlt eine standard Stueckelung und Waehrungssymbole: e=euro, p10: 1 und Primzahlen bis 10, p100 1 und Primzahlen bis 100, ein angefüger Stern * nimmt 1 aus. T=Taler")
    args=parser.parse_args()
    _verbosity=args.v
    p("Input",10)
    p(args,10)
    
    if args.d_stueck!=None:
        stueck=ststueck(args.d_stueck)
        einh=steinh(args.d_stueck)
    if args.stueck!=None:
        stueck=sorted(args.stueck)
    elif args.d_stueck==None:
        stueck=ststueck("e")
        
    if args.waehrung==None:
        if args.d_stueck==None:
            einh=steinh("e")
    else:
        for ws in args.waehrung:
            einh.append([ws,1.0])
        if args.umrechnung != None:
            for i in range(0,len(args.umrechnung)):
                einh[i][1]=args.umrechnung[i]
    einh.sort(key=lambda x: x[1])
    einh.reverse()
    p("Einheiten= "+str(einh), 6)
    p("Stueckelung= "+str(stueck), 6)
    p("Wechselgeldbetrag= "+str(args.Wechselgeld),6)
    a=geldberechnen(args.Wechselgeld, einh)
    betrag=dict()
    betrag[a]=[0, muenzzahl_zero(stueck)]
    p("Urspruengliches dictionary" + str(betrag),10)

    minstep=findminstep(stueck[0])

    b=a
    while b>0:
        p("/nGehe aus von key "+str(b),11)
        if b in betrag:
            for s in stueck:
                p("Pruefe Muenze mit Wert " + str(s),12)
                z=round(b-s,6) #6 willkürlich gewählt
                p("z="+str(z),11)
                if z in betrag:
                    if betrag[z][0]>betrag[b][0]+1:
                        betrag[z]=[betrag[b][0]+1, copy.copy(betrag[b][1])]
                        betrag[z][1][s]=betrag[z][1][s]+1
                else:
                    betrag[z]=[betrag[b][0]+1, copy.copy(betrag[b][1])]
                    betrag[z][1][s]=betrag[z][1][s]+1
        b=round(b-minstep,10)

    p("fertig", 8)
    p(betrag,12)
    p("\n\n",12)
    if 0.0 in betrag:
        i=0
    else:
        i=max(betrag.keys(), key=negval)
        p("Kein exaktes Resultat!", 5)
        p("Gib "+str(-i) + " zuviel heraus. Insgesamt: " + str(a-i), 4)

    p("Gebraucht werden "+str(betrag[i][0])+" Geldstuecke", 0)
    p("Beste Stueckelung:",5)
    pst(betrag[i][1], einh, 5)


    
def negval(v):
    if v<0:
        return v
    else:
        return float('-inf')

def findminstep(z):
    n=0
    while True:
        if z>10**-n:
            return 10**-n
        n=n+1

def muenzzahl_zero(stueck):
    l=dict()
    for i in stueck:
        l[i]=0
    return l



def ststueck(stri):
    stueckli=[]
    p("Standardstueckelung " + stri,7)
    if stri=="e" or stri=="euro":
        stueckli=[0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100, 200, 500]
        p("Euro",8)
    elif stri=="p10":
        stueckli=[1,2,3,5,7]
        p("p10",8)
    elif stri=="p10*":
        stueckli=[2,3,5,7]
        p("p10*",8)
    elif stri=="T":
        p("T",8)
        stueckli=[1, 3,6, 12, 24, 48, 72, 96, 144, 288]
    elif stri=="p100":
        stueckli=[1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
        p("p100",8)
    elif stri=="p100*":
        stueckli=[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
        p("p100*",8)
    return stueckli

    
def steinh(stri):
    if stri in ["e","euro"]:
        return [["cent", 0.01],["c", 0.01],["Euro", 1],["E", 1]]
    elif stri in ["T"]:
        return [ ["p", 12],["Pfennige", 1],["g", 12],["Groschen", 12], ["1/12 Taler", 24],["1/6 Taler", 48],["1/4 Taler", 72],["1/3 Taler", 96],["1/2 Taler", 144],["T",288], ["Taler",288]]
    else:
        return [["Einheiten",1]]




def pst(std, einh,  v):
    p("printing output aus "+str(std),9)
    for st in sorted(std.keys()):
        if std[st]>0:
            p(str(std[st])+" mal "+streinh(st, einh), v)

def geldberechnen(stri, einheiten):
    try:
        stri=stri.lower()
        geld=0.0
        p("Pruefe Eingabe",8)
        for einh in einheiten:
            p("Pruefe einheit " +str(einh[0]),9)
            if einh[0].lower() in stri:
                p("Einheit vorhanden",9)
                stli=stri.split(einh[0].lower())
                p("stli= "+str(stli),10)
                geld=geld+float(stli[0])*einh[1]
                p("Neues Gesamtgeld= " +str(geld),10)
                if len(stli)==1:
                    stri=""
                elif len(stli)==2:
                    stri=stli[1]
                elif len(stli)>2:
                    p("Error. Jede Einheit darf maximal 1x angegeben werden",0)
                p("stri wurde geaendert zu "+stri,9)
        if stri!="":
            geld=geld+float(stri)
        p("Eingabe verarbeitet zu geld: "+str(geld),8)
        return geld
    except:
        p("Fehler! Falsche Eingabe",0)
        p("Eingabe konnte nicht verarbeitet werden. Beachte: Einheiten muessen nachgestellt werden und groessere Einheiten vor kleineren genannt werden, dazwischen eine Zahl. Jede Einheit darf maximal 1x vorkommen.",4)
        exit()



def streinh(wert, einh):
    p("Einheitsumwandlung aus "+str(wert),10)
    stri=""
    for e in einh:
        z=0
        p("e="+str(e), 10)        
        while wert>=e[1]:
            z=z+1
            wert=round(wert-e[1],6) #Willkuerl 6
            p("z="+str(z), 10)
        if z>0:
            stri=stri+str(z)+ " " + e[0]+" "
    return stri


        
## VerbosityLevels:
##        0=nur 1 Zeile
##        5=default
##        6= Fortschrittsmeldungen
##        7=Detaillierte Fortschrittsmeldungen
##        8=Debug
##        9=Detaillierte Daten u Listen ausgeben
##        10=jede Kleinigkeit
def p(obj,lev):
    if _verbosity>=lev:
        print obj














if __name__ == "__main__":
    main()
