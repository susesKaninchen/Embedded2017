/*
 * pattern_save.c
 *
 * Created: 14.11.2017 08:44:53
 *  Author: Sven Marquardt
 */
#include "pattern_save.h"

//Die groesse die patterns einnehmen pro uint8_t
#define SIZE_PER_PATTERN_SLICE 4

typedef struct pattern_save {
	//Speicher für die patterns
	uint8_t patterns[UINT8_MAX];
	//Index des momentan durchlaufenden patterns
	uint16_t index;
	//momentan gefuellte groesse der patterns
	uint16_t size;
};

pattern_save_t * patteern_save_create_new() {

	pattern_save_t pattern_save;
	pattern_save.index = 0;
	pattern_save.size=1;
	return &pattern_save;

}
//Hole den wert mit index
uint8_t pattern_save_get_next_with_index(pattern_save_t *pattern_save,
		uint16_t index) {
	//Erhalte den ersten pattern slice
	uint8_t index_without_offset = index / SIZE_PER_PATTERN_SLICE;
	if (index_without_offset > UINT8_MAX) {
		return 0;
	}
	uint8_t buffer_pattern = pattern_save->patterns[index_without_offset];
	uint8_t index_in_pattern = index % SIZE_PER_PATTERN_SLICE;
	return ((buffer_pattern >> index_in_pattern) & 1) | ((buffer_pattern >> (index_in_pattern+1))&1);
}

uint8_t pattern_save_has_next(pattern_save_t *pattern_save) {

	if (pattern_save->index >= pattern_save->size) {
		return 0;
	}
	return 1;

}

uint8_t pattern_save_get_next(pattern_save_t *pattern_save){
	uint8_t buffer = pattern_save_get_next_with_index(pattern_save,pattern_save.index);
	pattern_save->index+=2;
	return buffer;
}

uint8_t pattern_save_save_new_patter(pattern_save_t *pattern_save,uint8_t pattern){
	uint8_t index_in_pattern = pattern_save.index%SIZE_PER_PATTERN_SLICE;
	uint8_t index_without_offset = pattern_save.index/SIZE_PER_PATTERN_SLICE;
	uint8_t old_pattern_value = pattern_save->patterns[index_in_pattern];
	if(index_in_pattern!=0){
		old_pattern_value = ((old_pattern_value >> index_in_pattern) | pattern)| ((old_pattern_value >> index_in_pattern+1)| pattern);
	}
	pattern_save->patterns[index_without_offset]=old_pattern_value;
	pattern_save.index+=2;
	pattern_save.size++;
	return 1;
}
uint8_t pattern_save_set_iterator_begin(pattern_save_t *pattern_save){
	pattern_save.index=0;
	return 1;
}



