SRC = *.cpp

FLAGS = -Wall -Wextra

NAME = -o gomoku

all:
	g++ $(FLAGS) $(NAME) $(SRC) -I ./
