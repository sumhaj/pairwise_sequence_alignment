pairwise_alignment_algorithm_v1.0.0: main.o  io.o substitution_matrix.o psa.o
	g++ main.o io.o substitution_matrix.o psa.o -o pairwise_alignment_algorithm_v1.0.0

main.o: main.cpp
	g++ -c main.cpp

io.o: io/io.cpp io/io.hpp
	g++ -c io/io.cpp

substitution_matrix.o: substitution_matrix/substitution_matrix.cpp substitution_matrix/substitution_matrix.hpp
	g++ -c substitution_matrix/substitution_matrix.cpp

psa.o: psa/psa.cpp psa/psa.hpp
	g++ -c psa/psa.cpp

clean:
	rm *.o pairwise_alignment_algorithm_v1.0.0