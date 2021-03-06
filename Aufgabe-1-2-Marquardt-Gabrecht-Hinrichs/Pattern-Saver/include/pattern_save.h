/*
 * pattern_save.h
 *
 * Created: 14.11.2017 08:25:22
 *  Author: Sven Marquardt
 */ 
#ifndef PATTERN_SAVE_H_
#include <inttypes.h>

#define PATTERN_UP 3
#define PATTERN_DOWN 2
#define PATTERN_LEFT 1
#define PATTERN_RIGHT 0
//Speichert das Pattern und zugeh�rige attribute um den zugriff zu sichern.
typedef struct pattern_save pattern_save_t;
//Erhalte einen neuen Speicher f�r patterns
pattern_save_t * pattern_save_create_new();
//Erhalte das n�chste pattern. Schiebt den iterator um einen nach vorne. Error bei ueberschreitung der groesse. Vorher also has_next_pattern aufrufen
uint8_t pattern_save_get_next(pattern_save_t * pattern_save);
//speicher ein neues pattern an der stelle des iterators
uint8_t pattern_save_save_new_pattern(pattern_save_t * pattern_save,uint8_t new_pattern);
//Liefert 1 wenn ein n�chstes pattern vorhanden ist. 0 wenn kein weiteres vorhanden ist
uint8_t pattern_save_has_next(pattern_save_t *pattern_save);
//Setzt den Iterator auf den anfang des Speichers
uint8_t pattern_save_set_iterator_begin(pattern_save_t *pattern_save);
//Free das pattern save
void pattern_save_free(pattern_save_t * pattern_save);
//Speicher wieder freigeben für neue werte
void pattern_save_clean(pattern_save_t *pattern_save_ptr);
//groesse
uint8_t pattern_save_get_size(pattern_save_t * pattern_save_ptr);


#endif /* PATTERN_SAVE_H_ */