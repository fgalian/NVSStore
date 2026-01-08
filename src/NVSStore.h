#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class NVSStore {
public:
  // Acceso único (singleton)
  static NVSStore& instance();

  // --- SET (tipos primitivos) ---
  bool setBool  (const char* page, const char* key, bool value);
  bool setInt   (const char* page, const char* key, int32_t value);
  bool setLong  (const char* page, const char* key, int32_t value);   // 32-bit
  bool setDouble(const char* page, const char* key, double value);

  // --- SET (cadenas C) ---
  // Guarda 'value' (char*) en NVS. Devuelve true si escribió algo.
  bool setChars (const char* page, const char* key, const char* value);
  // Versión con clave formateada, ej: fmtKey="NOMBRE_%d"
  bool setCharsf(const char* page, const char* fmtKey, int id, const char* value);

  // Helpers SET con clave formateada (primitivos)
  bool setBoolf  (const char* page, const char* fmtKey, int id, bool value);
  bool setIntf   (const char* page, const char* fmtKey, int id, int32_t value);
  bool setLongf  (const char* page, const char* fmtKey, int id, int32_t value);
  bool setDoublef(const char* page, const char* fmtKey, int id, double value);

  // --- GET (tipos primitivos) ---
  bool    getBool  (const char* page, const char* key, bool def=false);
  int32_t getInt   (const char* page, const char* key, int32_t def=0);
  int32_t getLong  (const char* page, const char* key, int32_t def=0); // 32-bit
  double  getDouble(const char* page, const char* key, double def=0.0);

  // Helpers GET con clave formateada (primitivos)
  bool    getBoolf  (const char* page, const char* fmtKey, int id, bool def=false);
  int32_t getIntf   (const char* page, const char* fmtKey, int id, int32_t def=0);
  int32_t getLongf  (const char* page, const char* fmtKey, int id, int32_t def=0);
  double  getDoublef(const char* page, const char* fmtKey, int id, double def=0.0);

  // --- GET (cadenas C) ---
  // Lee la cadena en 'out' (si no existe, escribe 'def' o "").
  // Devuelve true si la clave existía en NVS.
  bool getChars (const char* page, const char* key, char* out, size_t outsz, const char* def = "");

  // Igual que arriba pero con clave formateada ("XXX_%d").
  bool getCharsf(const char* page, const char* fmtKey, int id, char* out, size_t outsz, const char* def = "");

  // --- utilidades ---
  bool removeKey(const char* page, const char* key);
  bool clearPage(const char* page);

private:
  NVSStore();
  NVSStore(const NVSStore&) = delete;
  NVSStore& operator=(const NVSStore&) = delete;

  // Abre el namespace (RO/RW) si es necesario; devuelve false si falla.
  bool ensure(const char* page, bool readOnly);
  void endIfOpen();

  Preferences prefs_;
  SemaphoreHandle_t mtx_;
  String openNs_;      // uso interno
  bool isOpen_ = false;
  bool readOnly_ = true;
};
