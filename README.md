# RS038-pregledac-testova
##Pregledac testova
Program koji na osnovu ulaza, koji je u vidu fotografije i predstavlja multiple choice answer sheet, racuna koliko je student imao tacnih odgovora i koju ocenu je dobio. Problem se resava koristeci OMR - Optical Mark Recognition. Proces se zasniva na prikupljanju podataka prepoznavajuci delove koji su oznaceni na dokumentu koji se analizira.


Algoritam se moze opisati kroz nekoliko koraka:

* Preprocesiranje u kom se pretvara u crno-belu fotografiju tj. binarizacija
* Detektovanje linija koje predstavljaju ivice dokumenta
* Pronalazi se presek detektovanih ivica i formira pravougaonik
* Detektovanje krugova na dokumentu
* Pronalazenje krugova koji imaju odredjen procenat popunjenosti i oznacavamo ih kao popunjene


Program ce imati graficki interfejs koji ce korisnicima olaksati rad.
 
