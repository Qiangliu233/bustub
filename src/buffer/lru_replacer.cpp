//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {}

LRUReplacer::~LRUReplacer() = default;

auto LRUReplacer::Victim(frame_id_t *frame_id) -> bool { 
  
  latch.lock();
  if (lruMap.empty()) {
    latch.unlock();
    return false;
  }

  
  frame_id_t lru_frame = lru_list.back();
  lruMap.erase(lru_frame);
  
  lru_list.pop_back();
  *frame_id = lru_frame;
  latch.unlock();
  return true;
 }

void LRUReplacer::Pin(frame_id_t frame_id) {
  latch.lock();

  if (lruMap.count(frame_id) != 0) {
    lru_list.erase(lruMap[frame_id]);
    lruMap.erase(frame_id);
  }

  latch.unlock();    
}

void LRUReplacer::Unpin(frame_id_t frame_id) {}

auto LRUReplacer::Size() -> size_t { return 0; }

}  // namespace bustub
