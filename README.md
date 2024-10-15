# Servidor HTTP en Qt

Este es un servidor HTTP simple implementado en C++ utilizando el framework Qt. El servidor escucha solicitudes HTTP entrantes y sirve archivos desde un directorio raíz especificado. Incluye una interfaz gráfica básica (GUI) construida con `QMainWindow` para iniciar y detener el servidor, elegir un puerto y especificar el directorio raíz para servir archivos.

## Características

- Maneja solicitudes HTTP `GET` para servir archivos.
- Sirve `index.html` por defecto cuando se solicita el directorio raíz (`/`).
- Registra toda la actividad del servidor (solicitudes, errores) en un visor de registros dentro de la GUI.
- Muestra errores como números de puerto inválidos o directorios raíz faltantes.
- Controles de inicio/detención del servidor desde la interfaz gráfica.

## Capturas de Pantalla

> **Agrega aquí algunas capturas de la interfaz si es posible.**

## Requisitos

- **Qt Framework** (Qt 6.x).
- **C++17 o posterior** (debido al uso de características modernas de C++).
- Un compilador de C++ (por ejemplo, g++, clang++ o MSVC).

### Clonar el repositorio

```bash
git clone https://github.com/tuusuario/qt-http-server.git
cd qt-http-server
