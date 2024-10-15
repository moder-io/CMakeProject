# Servidor HTTP en Qt

Este es un servidor HTTP simple implementado en C++ utilizando el framework Qt. El servidor escucha solicitudes HTTP entrantes y sirve archivos desde un directorio ra�z especificado. Incluye una interfaz gr�fica b�sica (GUI) construida con `QMainWindow` para iniciar y detener el servidor, elegir un puerto y especificar el directorio ra�z para servir archivos.

## Caracter�sticas

- Maneja solicitudes HTTP `GET` para servir archivos.
- Sirve `index.html` por defecto cuando se solicita el directorio ra�z (`/`).
- Registra toda la actividad del servidor (solicitudes, errores) en un visor de registros dentro de la GUI.
- Muestra errores como n�meros de puerto inv�lidos o directorios ra�z faltantes.
- Controles de inicio/detenci�n del servidor desde la interfaz gr�fica.

## Capturas de Pantalla

> **Agrega aqu� algunas capturas de la interfaz si es posible.**

## Requisitos

- **Qt Framework** (Qt 6.x).
- **C++17 o posterior** (debido al uso de caracter�sticas modernas de C++).
- Un compilador de C++ (por ejemplo, g++, clang++ o MSVC).

### Clonar el repositorio

```bash
git clone https://github.com/tuusuario/qt-http-server.git
cd qt-http-server
