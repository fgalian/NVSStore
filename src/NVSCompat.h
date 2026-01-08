// NVSCompat.h
#pragma once
#include "NVSStore.h"

namespace NVS {
  // Envoltorio cómodo para leer cadenas C directamente
  inline bool getChars(const char* page, const char* key, char* out, size_t outsz, const char* def = "") {
    return NVSStore::instance().getChars(page, key, out, outsz, def);
  }
  inline bool getCharsf(const char* page, const char* fmtKey, int id, char* out, size_t outsz, const char* def = "") {
    return NVSStore::instance().getCharsf(page, fmtKey, id, out, outsz, def);
  }
  inline bool getBool(const char* page, const char* key, bool def=false) {
    return NVSStore::instance().getBool(page, key, def);
  }
  inline bool getBoolf(const char* page, const char* fmtKey, int id, bool def=false) {
    return NVSStore::instance().getBoolf(page, fmtKey, id, def);
  }
  inline int32_t getInt(const char* page, const char* key, int32_t def=0) {
    return NVSStore::instance().getInt(page, key, def);
  }
  inline int32_t getIntf(const char* page, const char* fmtKey, int id, int32_t def=0) {
    return NVSStore::instance().getIntf(page, fmtKey, id, def);
  }


  inline bool setChars(const char* page, const char* key, const char* value) {
    return NVSStore::instance().setChars(page, key, value);
  }
  inline bool setCharsf(const char* page, const char* fmtKey, int id, const char* value) {
    return NVSStore::instance().setCharsf(page, fmtKey, id, value);
  }
  inline bool setBool(const char* page, const char* key, bool v) {
    return NVSStore::instance().setBool(page, key, v);
  }
  inline bool setBoolf(const char* page, const char* fmtKey, int id, bool v) {
    return NVSStore::instance().setBoolf(page, fmtKey, id, v);
  }
  inline bool setInt(const char* page, const char* key, int32_t value) {
    return NVSStore::instance().setInt(page, key, value);
  }
  inline bool setIntf(const char* page, const char* fmtKey, int id, int32_t v) {
    return NVSStore::instance().setIntf(page, fmtKey, id, v);
  }
  
  // --- utilidades ---
  inline bool removeKey(const char* page, const char* key) {
    return NVSStore::instance().removeKey(page, key);
  }

  inline bool clearPage(const char* page) {
    return NVSStore::instance().clearPage(page);
  }

  // … añade los que uses a menudo (getInt, setInt, etc.)
}
