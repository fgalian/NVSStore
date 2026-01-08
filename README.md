# NVSStore

**NVSStore** es una librería Arduino para **ESP32** que proporciona una capa de abstracción robusta, reutilizable y mantenible sobre el sistema **NVS (Non-Volatile Storage)**, facilitando el almacenamiento persistente de configuración y estado en dispositivos IoT.

La librería está diseñada como un **singleton centralizado**, pensada para ser compartida entre múltiples proyectos y firmwares, siguiendo buenas prácticas de arquitectura de software embebido y reutilización de código.

---

## 🏢 Sobre la empresa

**FG Tech Software S.L.** es una empresa tecnológica especializada en el desarrollo de soluciones **IoT**, **software empresarial** y **firmware embebido**, con un fuerte enfoque en la calidad del código, la mantenibilidad a largo plazo y la estandarización de arquitecturas técnicas.

Como parte de su compromiso con la **innovación abierta**, FG Tech Software S.L. libera al mercado componentes de su ecosistema interno en forma de **código fuente reutilizable**, permitiendo que la comunidad técnica pueda:
- reutilizar librerías probadas en entornos reales,
- auditar y mejorar el código,
- y acelerar el desarrollo de nuevos proyectos IoT.

Este repositorio forma parte de esa estrategia de apertura y colaboración.

---

## 🎯 Objetivos de la librería

- Centralizar el acceso a NVS en dispositivos ESP32  
- Evitar duplicación de código entre firmwares  
- Proporcionar una API coherente y estable  
- Facilitar la evolución y mantenimiento de proyectos IoT  
- Permitir compatibilidad con código legacy mediante capas auxiliares  

---

## ✨ Características principales

- Singleton `NVSStore` accesible globalmente  
- Métodos tipados para:
  - `int`
  - `bool`
  - `char* / strings`
- Gestión de *namespaces* y claves  
- Funciones de borrado y limpieza (`removeKey`, `clearPage`)  
- Capa de compatibilidad (`NVSCompat`) para facilitar migraciones  
- Compatible con **Arduino ESP32 Core**  

---

## 📦 Estructura del repositorio

```text
NVSStore/
├── library.properties
├── README.md
└── src/
    ├── NVSStore.h
    ├── NVSStore.cpp
    └── NVSCompat.h
```

---

## 🔧 Requisitos

- Microcontroladores **ESP32**  
- Arduino IDE o `arduino-cli`  
- Core ESP32 instalado (`esp32:esp32`)  
- Arquitectura soportada: **esp32**  

---

## ⬇️ Instalación

### Opción 1 — Instalación manual (recomendada)

```bash
mkdir -p ~/Arduino/libraries
cd ~/Arduino/libraries
git clone https://github.com/fgalian/NVSStore.git
```

El directorio debe llamarse exactamente:

```text
~/Arduino/libraries/NVSStore
```

---

### Opción 2 — Uso como submódulo Git (entornos profesionales)

```bash
git submodule add https://github.com/fgalian/NVSStore.git libs/NVSStore
ln -s $(pwd)/libs/NVSStore ~/Arduino/libraries/NVSStore
```

Esta opción es adecuada para **monorepos** y proyectos con control estricto de versiones.

---

## 🚀 Uso básico

Incluye la librería en tu firmware:

```cpp
#include <NVSStore.h>
```

### Ejemplos

#### Guardar y leer un valor entero
```cpp
NVSStore::instance().setInt("config", "modo", 1);
int modo = NVSStore::instance().getInt("config", "modo", 0);
```

#### Guardar un valor booleano
```cpp
NVSStore::instance().setBool("config", "debug", true);
```

#### Guardar una cadena de texto
```cpp
NVSStore::instance().setChars("wifi", "ssid", "MiRedWiFi");
```

---

## 🔁 Compatibilidad legacy (`NVSCompat`)

Para facilitar la adopción en proyectos existentes, se incluye una capa de compatibilidad:

```cpp
#include <NVSCompat.h>

NVS::setInt("config", "modo", 1);
int modo = NVS::getInt("config", "modo", 0);
```

Esta capa permite migraciones progresivas sin refactorizaciones agresivas.

---

## 🧪 Verificación de la instalación

Compila tu proyecto en modo verbose:

```bash
arduino-cli compile --verbose
```

Deberías ver una línea similar a:

```text
Using library NVSStore at version 1.0.0
```

---

## 🧱 Filosofía de diseño

- Librería independiente y versionada  
- Separación clara entre firmware de aplicación y código común  
- Preparada para proyectos IoT multi-dispositivo  
- Orientada a entornos profesionales y producción  

---

## 🤝 Comunidad y reutilización

FG Tech Software S.L. fomenta el uso, estudio y reutilización de este código por parte de la comunidad.  
Se aceptan *issues*, propuestas de mejora y *pull requests* alineados con la filosofía del proyecto.

---

## 📄 Licencia

Este proyecto se distribuye bajo licencia **AGPL v3**.  
El uso del código implica la aceptación de los términos de dicha licencia.

---

## 📬 Contacto

**FG Tech Software S.L.**  
GitHub: https://github.com/fgalian
