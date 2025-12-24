`hay casos incorrectos al usar env -i ./minishell`

Al iniciar en el main cargo PWD y OLDPWD para que funcionen los cd
Si quieres usar programas hay que setear PATH a mano. Por lo demas 
he arreglado los problemas que hay a no cargar nada de entorno.
	
`y algún caso de cd`

Los casos de cd y de echo en general son problema del tokenizado. Un problema en el tokenizado implica que cualquier comando que usemos va a propagar los args incorrectamente.

