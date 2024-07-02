file(REMOVE_RECURSE
  "libSTM32412G-Discovery.a"
  "libSTM32412G-Discovery.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C CXX)
  include(CMakeFiles/STM32412G-Discovery.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
