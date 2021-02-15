NAME = RDS
#SRCS = Building/*.hpp Resource/*.hpp Individual/*.hpp Map/*.hpp Drone/*.hpp Executive.hpp ID.hpp MainAI.hpp main.cpp
OBJS = objs/Building/Building.o objs/Building/FulfillmentCenter.o objs/Building/House.o objs/Building/Office.o \
 objs/Drone/CargoDrone.o objs/Drone/Drone.o objs/Drone/PassengerDrone.o objs/Individual/Individual.o \
 objs/Resource/Resource.o objs/Executive.o objs/ID.o objs/Location.o objs/main.o \
 objs/MainAI.o
HEADERS = inc/rds.hpp
CFLAGS = -Wall -Wextra #-Werror
STD = -std=c++11

all: $(NAME)

$(NAME): $(OBJS)
	g++ $(CFLAGS) $(STD) $(OBJS) -o $(NAME)

$(OBJS): objs/%.o: src/%.cpp $(HEADERS)
	g++ $(CFLAGS) $(STD) -c $< -o $@

clean:
	rm -f objs/*.o
	make clean -C RDS

fclean: clean
	rm -f $(NAME)
	make fclean -C RDS

re: fclean all

.PHONY : all clean fclean re