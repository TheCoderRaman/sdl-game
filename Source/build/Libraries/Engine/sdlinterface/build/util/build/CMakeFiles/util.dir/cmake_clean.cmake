FILE(REMOVE_RECURSE
  "../../../../../../libutil.pdb"
  "../../../../../../libutil.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/util.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
