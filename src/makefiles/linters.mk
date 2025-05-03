style: 
	find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec clang-format -n -style=Google {} +
	! find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec grep -n '[А-Яа-яЁё]' {} +

style_fix: 
	find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec clang-format -i -style=Google {} +

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-level=exhaustive $(SOURCE_DIR)

comments:
	find $(SOURCE_DIR) -type f -name "*.[c,h]" -exec grep -n '// ' {} +