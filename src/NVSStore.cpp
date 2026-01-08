#include "NVSStore.h"
#include <cstring>   // strlcpy

NVSStore& NVSStore::instance() {
  static NVSStore inst;
  return inst;
}

NVSStore::NVSStore() {
  mtx_ = xSemaphoreCreateMutex();
}

bool NVSStore::ensure(const char* page, bool ro) {
  if (!page || !*page) return false;
  if (xSemaphoreTake(mtx_, portMAX_DELAY) != pdTRUE) return false;

  // reabrir si cambia página o modo
  if (!isOpen_ || openNs_ != page || readOnly_ != ro) {
    if (isOpen_) { prefs_.end(); isOpen_ = false; }
    if (!prefs_.begin(page, ro)) { xSemaphoreGive(mtx_); return false; }
    isOpen_ = true; openNs_ = page; readOnly_ = ro;
  }
  return true; // deja el mutex tomado: lo soltamos en cada método
}

void NVSStore::endIfOpen() {
  if (isOpen_) { prefs_.end(); isOpen_ = false; openNs_ = ""; }
  // soltamos el mutex en el método que llamó
}

/************ SET ************/
// // String (desactivado)
// bool NVSStore::setString(const char* page, const char* key, const char* value) {
//   if (!ensure(page, /*ro*/false)) return false;
//   size_t n = prefs_.putString(key, value ? value : "");
//   xSemaphoreGive(mtx_);
//   return n > 0;
// }

// char*
bool NVSStore::setChars(const char* page, const char* key, const char* value) {
  if (!ensure(page, /*ro*/false)) return false;
  size_t n = prefs_.putString(key, value ? value : "");
  xSemaphoreGive(mtx_);
  return n > 0;
}

bool NVSStore::setBool(const char* page, const char* key, bool value) {
  if (!ensure(page, false)) return false;
  size_t n = prefs_.putBool(key, value);
  xSemaphoreGive(mtx_);
  return n > 0;
}

bool NVSStore::setInt(const char* page, const char* key, int32_t value) {
  if (!ensure(page, false)) return false;
  size_t n = prefs_.putInt(key, value);
  xSemaphoreGive(mtx_);
  return n > 0;
}

bool NVSStore::setLong(const char* page, const char* key, int32_t value) {
  if (!ensure(page, false)) return false;
  size_t n = prefs_.putLong(key, value);
  xSemaphoreGive(mtx_);
  return n > 0;
}

bool NVSStore::setDouble(const char* page, const char* key, double value) {
  if (!ensure(page, false)) return false;
  size_t n = prefs_.putDouble(key, value);
  xSemaphoreGive(mtx_);
  return n > 0;
}

/************ SET (formateado) ************/
static inline void makeKey(char* out, size_t sz, const char* fmt, int id) {
  snprintf(out, sz, fmt, id);
}

// // String (desactivado)
// bool NVSStore::setStringf(const char* page, const char* fmtKey, int id, const char* value) {
//   char key[32]; makeKey(key, sizeof(key), fmtKey, id);
//   return setString(page, key, value);
// }

// char*
bool NVSStore::setCharsf(const char* page, const char* fmtKey, int id, const char* value) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return setChars(page, key, value);
}

bool NVSStore::setBoolf(const char* page, const char* fmtKey, int id, bool value) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return setBool(page, key, value);
}
bool NVSStore::setIntf(const char* page, const char* fmtKey, int id, int32_t value) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return setInt(page, key, value);
}
bool NVSStore::setLongf(const char* page, const char* fmtKey, int id, int32_t value) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return setLong(page, key, value);
}
bool NVSStore::setDoublef(const char* page, const char* fmtKey, int id, double value) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return setDouble(page, key, value);
}

/************ GET ************/
// // String (desactivado)
// String NVSStore::getString(const char* page, const char* key, const char* def) {
//   if (!ensure(page, /*ro*/true)) return String(def ? def : "");
//   String s = prefs_.getString(key, def ? def : "");
//   xSemaphoreGive(mtx_);
//   return s;
// }

// char*
bool NVSStore::getChars(const char* page, const char* key,
                        char* out, size_t outsz, const char* def) {
  if (!out || outsz == 0) return false;
  out[0] = '\0';

  if (!ensure(page, /*readOnly*/ true)) {
    if (def) strlcpy(out, def, outsz);
    return false;
  }

  size_t n = prefs_.getString(key, out, outsz);
  xSemaphoreGive(mtx_);

  if (n == 0) { // clave no existe → usa 'def'
    if (def) strlcpy(out, def, outsz);
    return false;
  }
  return true;
}

bool NVSStore::getBool(const char* page, const char* key, bool def) {
  if (!ensure(page, true)) return def;
  bool v = prefs_.getBool(key, def);
  xSemaphoreGive(mtx_);
  return v;
}

int32_t NVSStore::getInt(const char* page, const char* key, int32_t def) {
  if (!ensure(page, true)) return def;
  int32_t v = prefs_.getInt(key, def);
  xSemaphoreGive(mtx_);
  return v;
}

int32_t NVSStore::getLong(const char* page, const char* key, int32_t def) {
  if (!ensure(page, true)) return def;
  int32_t v = prefs_.getLong(key, def);
  xSemaphoreGive(mtx_);
  return v;
}

double NVSStore::getDouble(const char* page, const char* key, double def) {
  if (!ensure(page, true)) return def;
  double v = prefs_.getDouble(key, def);
  xSemaphoreGive(mtx_);
  return v;
}

/************ GET (formateado) ************/
// // String (desactivado)
// String  NVSStore::getStringf(const char* page, const char* fmtKey, int id, const char* def) {
//   char key[32]; makeKey(key, sizeof(key), fmtKey, id);
//   return getString(page, key, def);
// }

// char*
bool NVSStore::getCharsf(const char* page, const char* fmtKey, int id, char* out, size_t outsz, const char* def) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return getChars(page, key, out, outsz, def);
}

bool NVSStore::getBoolf(const char* page, const char* fmtKey, int id, bool def) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return getBool(page, key, def);
}
int32_t NVSStore::getIntf(const char* page, const char* fmtKey, int id, int32_t def) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return getInt(page, key, def);
}
int32_t NVSStore::getLongf(const char* page, const char* fmtKey, int id, int32_t def) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return getLong(page, key, def);
}
double  NVSStore::getDoublef(const char* page, const char* fmtKey, int id, double def) {
  char key[32]; makeKey(key, sizeof(key), fmtKey, id);
  return getDouble(page, key, def);
}

/************ utilidades ************/
bool NVSStore::removeKey(const char* page, const char* key) {
  if (!ensure(page, false)) return false;
  bool ok = prefs_.remove(key);
  xSemaphoreGive(mtx_);
  return ok;
}

bool NVSStore::clearPage(const char* page) {
  if (!ensure(page, false)) return false;
  bool ok = prefs_.clear();
  xSemaphoreGive(mtx_);
  return ok;
}
