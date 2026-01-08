# Changelog

Todos los cambios relevantes de este proyecto se documentarán en este fichero.

El formato sigue las recomendaciones de **Keep a Changelog** y el versionado utiliza un esquema basado en fecha (`YYYY.M.D`), alineado con la evolución real del firmware y las librerías del ecosistema ThinksIoT.

---

## [2026.1.8] - 2026-01-08

### 🚀 Versión inicial

Primera liberación pública de la librería **NVSStore** como componente independiente y reutilizable.

### ✨ Añadido
- Implementación del singleton `NVSStore` para acceso centralizado a NVS.
- Abstracción completa sobre `Preferences` del core ESP32.
- Métodos tipados para almacenamiento persistente:
  - `bool`
  - `int32_t`
  - `long`
  - cadenas (`char*`)
- Gestión optimizada de *namespaces* con reapertura inteligente.
- Control de acceso concurrente mediante **FreeRTOS mutex**.
- Funciones auxiliares:
  - `removeKey`
  - `clearPage`
- Capa de compatibilidad `NVSCompat` para proyectos legacy.
- Soporte para claves formateadas (`getCharsf`, `setCharsf`, etc.).

### 🏗️ Arquitectura
- Separación clara entre API pública y lógica interna.
- Diseñada para reutilización en múltiples firmwares ESP32.
- Preparada para entornos IoT de producción.

### 📦 Infraestructura
- Estructura estándar de librería Arduino (`library.properties`, `src/`).
- Publicación como repositorio Git independiente.
- Documentación inicial (`README.md`) orientada a uso profesional y comunitario.

---

## Convenciones de versionado

- **Mayor**: cambios incompatibles en la API pública.
- **Menor**: nuevas funcionalidades compatibles.
- **Parche**: correcciones internas y mejoras sin impacto funcional.

---

## Licencia

Este proyecto se distribuye bajo licencia **AGPL v3**.
