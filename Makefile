.PHONY: clean All

All:
	@echo "----------Building project:[ CPrime - Debug ]----------"
	@cd "CPrime" && "$(MAKE)" -f  "CPrime.mk"
clean:
	@echo "----------Cleaning project:[ CPrime - Debug ]----------"
	@cd "CPrime" && "$(MAKE)" -f  "CPrime.mk" clean
