#include <unistd.h>
#include <stdio.h>
// dif
#include <math.h>
// dif

int ft_close(FILE *file) {
	write(1, "Error: Operation file corrupted\n", 32);
	fclose(file);
	return 1;
}

int main(int argc, char **argv) {
	FILE *file;
	int i = -1, j, height, width, arg;
	char back, c, symb;
	// dif
	float x, y, radius, res;
	// dif
	if(argc != 2)
		return(write(1, "Error: argument\n", 16) && 1);
	if(!(file = fopen(argv[1], "r")))
		return(write(1, "Error: Operation file corrupted\n", 32) && 1);
	// dif
	if((arg = fscanf(file, "%d %d %c\n", &width, &height, &back)) != 3) // dif
		return(ft_close(file));
	if(width <= 0 || width > 300 || height <= 0 || height > 300)
		return(ft_close(file));
	char arr[height][width];
	while(++i < height) {
		j = -1;
		while(++j < width)
			arr[i][j] = back;
	}
	// dif
	while((arg = fscanf(file, "%c %f %f %f %c\n", &c, &x, &y, &radius, &symb)) == 5) { //dif
		if((c != 'c' && c != 'C') || radius <= 0)
			return(ft_close(file));
		i = -1;
		while(++i < height) {
			j = -1;
			while(++j < width) {  // dif
				res = sqrt(pow(i - y, 2) + pow(j - x, 2));
				if(res <= radius)
					if((radius - res < 1 && c == 'c') || c == 'C') // dif
						arr[i][j] = symb;
			}
		}
	}
	if (arg > 0 && arg != 5)
		return(ft_close(file));
	i = -1;
	while(++i < height) {
		j = -1;
		while(++j < width)
			write(1, &arr[i][j], 1);
		write(1, "\n", 1);
	}
	return(fclose(file) && 0);
}
