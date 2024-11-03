Aktuální stav

_Přepínání scén za běhu_: 
Ano, pomocí klavesy tab, logika se nachází ve třídě Application

a) Základní scéna - Ano

b) Scéna s lesem - Ano

c) Scéna se čtyřmi kuličkami - Ano

d) Scéna pro demonstraci použití všech shaderů (Konstantní, Lambert, Phong a Blinn) - Ano

_Světlo_ - Ano, zdroj je zadán natvrdo v shaderu

_Základní třídy_:
Třída DrawableObject sjednocuje model a shader, o shadery se stará ShaderFactory (jedna na scenu). 

_Transformace (Composite pattern)_:
Použil jsem abstrakntní třídu Transformation, ze které dědí Rotation, Translation, Scaling a CompoundTransformation (implementace patternu)

Základy OOP

a) _Encapsulation (zapouzdření)_ - ID shader programu a ostatní citlivá data jsou zapouzdřeny

b) _Inheritance (dědičnost)_ - kromě transformací taky použivám pro sceny (je základní třída Scene se společnou logikou a její potomci, tj. jednotlivé sceny)

c) _Polymorphism (polymorfismus neboli mnohotvárnost)_ - všude, kde se používá dědičnost: pattern Composite, vytvoření sceny (každá scena přetěžuje virtuální metodu CreateDrawableObjects, ale v aplikaci se s nimi pracuje jako s obecnymi sceny)

_Vertex a fragment shadery prosím uložte do textových souboru a použijte přiložený ShaderLoader pro jejich načítání (Ano/Ne) (Kde a jak jste použili?):_
Požívám statický ShaderLoader v ShaderFactory pro čtění z souborů.