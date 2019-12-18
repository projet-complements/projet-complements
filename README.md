Notre main se trouve dans match.cpp.
Pour avoir le vecteur contenant les protéines de la query, on a recourt à la classe Letter, qui convertit les protéines qu'on lit dans le fichier .fasta en int8_t afin de pouvoir les comparer à la database psq.

Ensuite on crée dans le main un objet de type "index", qui a pour attributs toutes les données soutirées du fichier .pin.

On appelle ensuite une fonction dans le main, qui va prendre les protéines dans la database .psq et les mettre dans un tableau.(appelé db)

On crée un objet de type "matrice" qui contient la matrice BLOSUM.
On crée alors un objet "algo", qui prend en paramètre la database, la query, la matrice BLOSUM et les gap open/extension ainsi que l'offset (qu'on a soutiré du .pin)

ainsi, on peut trouver les scores pour toutes les séquences, contenu dans un tableau qui est un attribut de l'objet "algo".
Les indices du tableau score sont les mêmes que ceux utilisés dans les offsets, ce qui lie les offsets de .psq et .phr

On cherche ensuite les 10 maximums dans le tableau score et on les affiche, aussi bien avec des cout que dans un fichier txt (results.txt), en gardant leur indice pour trouver l'offset.

Néanmoins, il est à noter que notre code marche pour une database réduite (newE.fasta) mais prend énormément de temps pour la database complète.
