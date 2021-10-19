#include <cstdio>

#include "Util.h"
#include "vector.h"

int main()
{
	FILE* queries = fopen("queries_1.txt", "r");

	int64_t appr_num_of_queries = get_approximate_number_of_queries(queries);

	fclose(queries);

	FILE* documents = fopen("queries_1.txt", "r");

	int64_t appr_num_of_documents = get_approximate_number_of_documents(documents);

	fclose(documents);

	return 0;
}
