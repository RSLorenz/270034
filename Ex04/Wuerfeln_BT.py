#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      Bernhard
#
# Created:     24.05.2011
# Copyright:   (c) Bernhard 2011
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python

import sys
import argparse
import random
import copy
_verbosity=2
random.seed()

def main():
    global _verbosity
    ## Comandline optionen verarbeiten
    parser=argparse.ArgumentParser(description="Zufallssequenzen unter erhaltung der Haeufigkeit.")
    parser.add_argument("-v", nargs='?', type=int, const=3, default=2 , help="Setzt den Verbositylevel zur angegebenen Zahl default=2, maximum=12, minimum=1.")
    parser.add_argument("Sequenz", type=str, help="Eingabe einer Buchstbensequenz (z.B: DNA-Basen)")
    parser.add_argument("-m", "--mode", type=int, default=7, help="1 fuer WUERFELN, 2 fuer SHUFFELN, 4 fuer DUPLETSHUFFEL,8 fuer progr_testen")
    args=parser.parse_args()

    sequenz=args.Sequenz
    _verbosity=args.v



    if args.mode%16>=8:
        if _verbosity>5:
            _verbosity=5
        if args.mode%2==1:
            neuesequenzen=[]
            for j in range(5):
                for i in range(100):
                    ns=wuerfel(sequenz)
                    neuesequenzen.append(ns)
##                random.seed()
            sdicts=[]
            for s in neuesequenzen:
                sdicts.append(bstdict(s,sequenz))
            p("sehr oft Wuerfeln:",2)
            for k in bstdict(sequenz,sequenz):
                mw= sum(d[k] for d in sdicts)/len(sdicts)
                p("Mittelwert " + str(k) +": "+str(mw),1)
                stdev=sum((d[k]-mw)**2 for d in sdicts)/(len(sdicts)-1)
                p("Stdabw " + str(k) +": "+str(stdev),2)
        if args.mode%4>=2:
            p("\n\nShuffeln \n",2)
            for i in range(10):
                print(shuffel(sequenz))
        if args.mode%8>=4:
            p("\n\nDuplets\n",2)
            erg=dict()
            for i in range(5):
                for j in range(300):
                    st=k_let(sequenz)
                    if st in erg.keys():
                        erg[st][i]+=1
                    else:
                        erg[st]=[0,0,0,0,0]
                        erg[st][i]=1
            for k in sorted(erg.keys()):
                print(k+" "+str(erg[k])+ " " +str(sum(erg[k])))
    else:
        if args.mode%2==1:
            p("\nGewuerfelt:",2)
            print(wuerfel(sequenz))
        if args.mode%4>=2:
            p("\ngeshuffelt:",2)
            print(shuffel(sequenz))
        if args.mode%8>=4:
            p("\nDuplets:",2)
            print(k_let(sequenz))



def wuerfel(seq):
    buchstaben=bstdict(seq,seq)
    p(buchstaben,3)
    newseq=""
    for i in range(len(seq)):
        newseq=newseq+wuerfel_buchstabe(buchstaben,len(seq))

    return newseq

##    p("Gewuerfelte Sequenz:",2)
##    p(newseq,1)
##
##    b2=dict()
##    for ch in newseq:
##        if ch in b2.keys():
##            b2[ch]+=1
##        else:
##            b2[ch]=1
##
##    for k in buchstaben.keys():
##        if k not in b2.keys():
##            b2[k]=0
##
##
##    if _verbosity>=2:
##        print("Buchstabe original random")
##        for k in buchstaben.keys():
##            print(str(k)+" --------"+str(buchstaben[k])+" -------"+str(b2[k]))

def bstdict(stri,vglstri):
    b=dict()
    for ch in stri:
        if ch in b.keys():
            b[ch]+=1.
        else:
            b[ch]=1.
        for ch in vglstri:
            if ch not in b.keys():
                b[ch]=0.
    return b

def wuerfel_buchstabe(buchst,l):
    r=random.random()
    w=0
    for k in buchst.keys():
        w=w+buchst[k]/l
        if r<w:
            return k
    return wuerfel_buchstabe(buchst,l)


def shuffel(seq):
    l=len(seq)
    newseq_li=[]
    for ch in seq:
        newseq_li.append(ch)
    for i in range(0, l-1):
        r=random.randint(i,l-1)
        c=newseq_li[i]
        newseq_li[i]=newseq_li[r]
        newseq_li[r]=c
    newseq="".join(newseq_li)
    return newseq

def k_let(seq):
    b=sorted(bstdict(seq,seq).keys())
    graph=[]
    for k in b:
        graph.append([])
        for j in b:
            graph[-1].append(0)

    for i in range(0,len(seq)-1):
        x=b.index(seq[i])
        y=b.index(seq[i+1])
        graph[x][y]+=1

    p("Graph: \n"+str(graph),4)

    stx=findstx(graph)
    p("starte mit "+b[stx],5)

    return b[stx]+findnext(graph, stx,b)

def findnext(gr,stx,b):
    s=sum(sum(gr[i]) for i in range(len(gr)))
##    p("Noch nicht abgearbeitete Ecken" + str(s),9)
    if s>0:
        if sum(gr[stx])>0:
            optionen=[]
            for i in range(len(gr)):
                optionen.append(1)
            while sum(optionen)>0:
                p("Optionen:"+str(optionen),8)
                p("Graph"+str(gr[stx]),8)
                r=random.randint(0,len(b)-1)
                p("r="+str(r),7)
                if optionen[r]==1:
                    optionen[r]=0
                    if gr[stx][r]>0:
                        p("r geht: " + b[r],6)
                        gr2=copy.deepcopy(gr)
                        gr2[stx][r]-=1
                        f= findnext(gr2,r,b)
                        if f!="":
                            p("Finde " +b[r],6)
                            return b[r]+f
                        else:
                            p("Vers. fehlerhaft",6)
                    else:
                        p("Buchstabe nicht anfahrbar: "+b[r],6)
                p("keine Option",7)
            p("**Zweig Fehlerhaft",6)
            return ""
        else:
            return ""
    else:
        return"!"

def findstx(gr):
    for i in range(len(gr)):
        if sum(gr[i])>sum(gr[x][i] for x in range(len(gr))):
            return i
    r = random.randint(0,len(gr)-1)
    return r
    

def p(stri, v):
    if v<=_verbosity:
        print(stri)

if __name__ == '__main__':
    main()
