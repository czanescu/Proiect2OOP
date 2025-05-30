Proiect 2+3 OOP în stadiul în care va fi / a fost prezentat la laborator

<p align="center">
  <img src="https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExNnI3MjM3dThzaGc5ZjB0eW01bmNnMWtuMGI2bXc4dmMxanl1bWp4NSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/VAOyQTIvIWfMybbKUF/giphy.gif" alt="Game">
</p>

Aplicația reprezintă un joc 2D, în care un jucător (poate fi orice sprite pătrat, dar am ales o broască) se poate mișca stânga și dreapta atâta timp cât se află pe o platformă. Odată ce jucătorul sare, viteza laterală a acestuia rămâne constantă până când acesta aterizează pe o platformă, unde se aplică un algoritm de frânare dacă nu se apasă tasta aferentă mișcării actuale (simulez forța de frecare). Calculul săriturii jucătorului este bazat pe o simulare a săriturii (se simulează o viteză inițială de săritură, iar apoi atâta timp cât jucătorul nu se află pe o platformă, acesta va continua să cadă cu o accelerație constantă).

Harta este formată din sprite-uri, care sunt încărcate din 3 fișiere separate (numele hărții + .sprites, .movable, .animated), sprite-urile trebuie să corespundă path-ului relativ din fișierul de hartă (dacă sunt toate sprite-urile dintr-un director comun, path-ul relativ al directorului comun se pune la începutul fișierului). Sprite-urile animate din fisierul .animated se află într-un director cu numele fișierului și sunt numite 0.png, 1.png, 2.png etc. (numărul de sprite-uri animate trebuie să fie cel puțin egal cu numărul de frame-uri de animație din fișierul .animated). Coordonatele sprite-urilor din fișiere sunt relative la un sprite de început poziționat în stânga jos a ecranului la momentul încărcării hărții, iar un sprite are înalțimea și lățimea de o unitate (la rezoluția 1920x1080 asta înseamnă 120x120px, deoarece sunt mereu 9 sprite-uri pe înălțime și 16 sprite-uri pe lățime).

La fiecare rulare, încărcarea sprite-urilor poate lua (în funcție de  platformă) între 1 (linux) și 3 secunde (windows), ceea ce este mult mai bine decât era înainte să schimb sprite-urile placeholder (3 secunde respectiv 10), încărcarea fiecărui sprite în memoria calculatorului luând o perioadă considerabilă. Din acest motiv, am inclus un loading screen care se va afișa până când toate sprite-urile sunt încărcate. De asemenea, am inclus un meniu de pauză care poate fi accesat apăsând tasta Escape.

Jocul utilizează sleep pentru a nu consuma CPU tot timpul, însă pe windows (sau cel puțin pe laptop-ul meu) implementarea de sleep nu este suficient de precisă pentru a putea face sleep mai puțin de un frame. Din acest motiv, pe windows face Sleep(0), pentru a elibera măcar threadul în caz că au nevoie alte task-uri să îl folosească.

Implementarea sunetului lasă de dorit, deoarece chiar dacă pe linux funcționează perfect (poate cu un delay minuscul prin căști bluetooth), pe windows prin căști are un delay de aproximativ 0.5 secunde (motivul pentru care am adăugat opționea de oprire a sunetului oricând din meniu).

Framerate-ul, rezoluția jocului și sunetul pot fi setate din fișierul .config (înainte de rulare). Framerate-ul poate fi oricât de mare sau mic, însă dacă este mai mare decât poate rula calculatorul, jocul nu va rula corect (se aplică asterisk-ul doar pe windows). De adăugat că rezoluția poate fi și ea setată la aproximativ orice număr, însă, dacă pe linux orice rezoluție mai mare decât rezoluția monitorului se comportă ca aceasta, pe windows jocul va încerca să deseneze la rezoluția setată, însă nu va reuși să o facă, iar jocul va avea un comportament anormal la trecerea de la un "tablou de joc" la altul. De asemenea, jocul este gândit să ruleze la un aspect ratio de 16:9, deci dacă rezoluția nu este 16:9, jocul va avea un aspect alungit, deoarece va rula streched.

Am adăugat și opțiunea ca jucătorul să poată folosi un controller (am testat atât pe Windows cât și pe Linux un controller de PlayStation 4), ocazie cu care am descoperit că aceleași butoane au nume diferite pe Windows respectiv Linux, de aceea am adăugat o clasă singleton Platform care se ocupă cu detectarea OS-ului la rulare și apoi funcționează ca un boolean global (chiar dacă este un enum) care poate fi folosit pentru a verifica ce OS este folosit, și deci pentru a folosi butoanele corecte pentru controller (și orice alte task-uri ce se fac diferit în funcție de OS-ul pe care rulează).

Requirement-uri tema 2 proiect (explicații mai detaliate în main):

- Moșteniri ✔
- Funcții virtuale pure ✔
- Apelarea constructorilor din clase derivate ✔
- Clasă cu atribut de tip pointer la o clasă de bază cu derivate ✔
- Excepții ✔
- Funcții și atribute statice ✔
- STL ✔

Requirement-uri tema 3 proiect (același asterisk ca la tema 2):

- elemente șablon ✔
- design patterns ✔

Instrucțiuni de compilare WINDOWS:
- Requirements:
  - SFML 2.5.0 pentru mingw pe 64 de biți
  - mingw g++ pe 64 de biți
  - CMAKE 3.10+
- Adăugați MinGW/bin la path
- setați locația directorului SFML în CMakeLists.txt
- rulați din fișierul de build comanda "cmake -G "MinGW Makefiles" ..", apoi "cmake --build ."
- dacă directorul de build este nou adăugați din directorul build-windows: directorul assets, fișierul .config și dll-urile.

Instrucțiuni de compilare LINUX:
- Requirements:
  - g++
  - libsfml-dev
  - cmake
- rulați din fișierul de build comanda "cmake ..", apoi "make"
- dacă directorul de build este nou adăugați din directorul build: directorul assets și fișierul .config.

Instrucțiuni de rulare:
rulați ./gravity.exe pe windows sau ./gravity pe linux (pe windows nu aveți nevoie de SFML pentru rulare deoarece am inclus dll-urile necesare, pe linux este necesar package-ul libsmfl-dev)
