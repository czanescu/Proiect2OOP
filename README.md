Proiect 2+3 OOP (actual doar proiect 2)

Aplicația reprezintă un joc 2D, în care un jucător (poate fi orice sprite patrat, dar actual este mario) se poate mișca stânga și dreapta atâta timp cât se află pe o platformă. Odată ce jucătorul sare, viteza laterală a acestuia rămâne constantă până când acesta aterizează pe o platformă, unde se aplică un algoritm de frânare dacă nu se apasă tasta aferentă mișcării actuale (simulez forța de frecare). Calculul săriturii jucătorului este bazat pe o simulare a săriturii (se simulează o viteză inițială de săritură, iar apoi atâta timp cât jucătorul nu se află pe o platformă, acesta va continua să cadă cu o accelerație constantă).

Harta este formată din sprite-uri, care sunt încărcate dintr 3 fișiere separate (numele hărții + .sprites, .movable, .animated), sprite-urile trebuie să corespundă path-ului relativ din fișierul de hartă (dacă sunt toate sprite-urile dintr-un fișier hartă dintr-un director comun, path-ul relativ al directorului comun se pune la începutul fișierului). Sprite-urile animate din fisierul .animated se află într-un director cu numele fișierului și sunt numite 0.png, 1.png, 2.png etc. (numărul de sprite-uri animate trebuie să fie cel puțin egal cu numărul de frame-uri de animație din fișierul .animated). Coordonatele sprite-urilor din fișiere sunt relative la un sprite de început la coordonatele (0, 0), iar un sprite are inaltimea si latimea de o unitate (la rezoluția 1920x1080 asta inseamna 120x120px,  deoarece sunt mereu 9 sprite-uri pe inaltime si 16 sprite-uri pe latime).

La fiecare rulare, încărcarea sprite-urilor poate lua (în funcție de  platformă) între 3 (linux) și 10 secunde (windows), probabil din cauza implementării librăriei SFML. Din acest motiv, am inclus un loading screen care se va afișa până când toate sprite-urile sunt încărcate. De asemenea, am inclus un meniu de pauză care poate fi accesat apăsând tasta Escape.

Jocul utilizează sleep pentru a nu consuma CPU tot timpul, însă pe windows implementarea de sleep nu este suficient de precisă pentru a putea face sleep mai puțin de un frame. Din acest motiv, pe windows face Sleep(0), pentru a elibera măcar threadul pentru alte task-uri.

Framerate-ul și rezoluția jocului pot fi setate din fișierul .config (înainte de rulare). Framerate-ul poate fi oricât de mare sau mic, însă dacă este mai mare decât poate rula calculatorul, jocul nu va rula corect. De adăugat că rezoluția poate fi si ea setata la aproximativ orice numar, insa, daca pe linux orice rezolutie mai mare decat rezolutia monitorului se comporta ca rezolutia monitorului, pe windows jocul va incerca sa deseneze la rezolutia setata, insa nu va reusi sa o faca, iar jocul va avea un comportament anormal la trecerea de la un "tablou de joc" la altul. De asemenea, jocul este gândit să ruleze la un aspect ratio de 16:9, deci dacă rezoluția nu este 16:9, jocul va fi streched.

Requirement-uri tema 2 proiect (explicații mai detaliate în main):

- Moșteniri ✔
- Funcții virtuale pure ✔
- Apelarea constructorilor din clase derivate ✔
- Clasă cu atribut de tip pointer la o clasă de bază cu derivate ✔
- Excepții ✔
- Funcții și atribute statice ✔
- STL ✔
