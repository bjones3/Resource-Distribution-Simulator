NAME = RDS
SRCS = Building/*.hpp Resource/*.hpp Individual/*.hpp Map/*.hpp Drone/*.hpp Executive.hpp ID.hpp MainAI.hpp main.cpp
OBJS = objs/*.o
HEADERS = rds.hpp
CFLAGS = -Wall #-Wextra -Werror
STD = -std=c++11
FRAMEWORKS = -framework Appkit -framework OpenGL

all: $(NAME)

$(NAME): $(OBJS)
	g++ $(CFLAGS) $(STD) $(OBJS) -o $(NAME)

$(OBJS): objs/%.o: $(SRCS) $(HEADERS)
	g++ $(CFLAGS) $(STD) -c $< -o $@

clean:
	rm -f objs/*.o
	make clean -C RDS

fclean: clean
	rm -f $(NAME)
	make fclean -C RDS

re: fclean all

.PHONY : all clean fclean re
