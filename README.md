<html>
<body>
<h1>TETRIS ++</h1>
<div style ="text-align: justify">
<h3>El clásico juego de Tetris, con una reversión: se juega completamente dentro de la consola.</h3>
<image src="./recursos/Muestra Inicio.png">
<h4>Escrito en <code>C++</code>. Únicas dependencias: la biblioteca estándar de C++, WinAPI.</h4>
</div>

<i><1>Nota: actualmente sólo compatible con Windows 7 o superior. Versión compatible con sistemas Unix en proceso.</i>

<h2>Jugar Tetris++</h2>
El juego es completamente portable, descargue y descomprima el archivo <a href="./TETRIS++_v0-1.zip"><code>TETRIS++_v0-1.zip</code></a>

<h2>Compilar Tetris++ desde fuente</h2>
Tetris++ tiene tan pocas dependencias que compilarlo con g++ es relativamente sencillo:

```Bash
g++ -o tetris++.exe main.cpp -static-libgcc -static-libstdc++ -static-lpthread
```

</body>
</html>
