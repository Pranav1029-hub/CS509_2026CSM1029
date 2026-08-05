#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations for drivers
int run_gemm_driver(const char *algo_type, const char *filepath, int block_size);
int run_csr_driver(const char *filepath, int source_vertex);

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void run_assignment_1_menu() {
    int choice;
    char filepath[256];
    int block_size = 32;
    int source_vertex = 0;

    while (1) {
        printf("\n=====================================================\n");
        printf("               CS509 - ASSIGNMENT 1                  \n");
        printf("=====================================================\n");
        printf("  1. Run GEMM Simple\n");
        printf("  2. Run GEMM Blocking\n");
        printf("  3. Run CSR Graph\n");
        printf("  4. Return to Main Assignment Menu\n");
        printf("-----------------------------------------------------\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (choice == 4) break;

        switch (choice) {
            case 1:
                printf("\nEnter input file path (e.g., assignment_01/Matrix_Multiplication/data/gemm_10.txt): ");
                scanf("%255s", filepath);
                run_gemm_driver("simple", filepath, 0);
                break;

            case 2:
                printf("\nEnter input file path (e.g., assignment_01/Matrix_Multiplication/data/gemm_10.txt): ");
                scanf("%255s", filepath);
                printf("Enter block size (default 32): ");
                if (scanf("%d", &block_size) != 1) block_size = 32;
                run_gemm_driver("blocking", filepath, block_size);
                break;

            case 3:
                printf("\nEnter input file path (e.g., assignment_01/CSR_Graph/data/csr_10.txt): ");
                scanf("%255s", filepath);
                printf("Enter source vertex (default 0): ");
                if (scanf("%d", &source_vertex) != 1) source_vertex = 0;
                run_csr_driver(filepath, source_vertex);
                break;

            default:
                printf("Invalid selection!\n");
        }
    }
}

int main(int argc, char *argv[]) {
    // Non-interactive command-line mode support (if arguments passed directly)
    if (argc >= 3) {
        const char *algo = argv[1];
        const char *filepath = argv[2];

        if (strcmp(algo, "gemm_simple") == 0) {
            return run_gemm_driver("simple", filepath, 0);
        } else if (strcmp(algo, "gemm_blocking") == 0) {
            int block_size = (argc >= 4) ? atoi(argv[3]) : 32;
            return run_gemm_driver("blocking", filepath, block_size);
        } else if (strcmp(algo, "csr") == 0) {
            int source = (argc >= 4) ? atoi(argv[3]) : 0;
            return run_csr_driver(filepath, source);
        }
    }

    // Interactive Menu Mode
    int assignment_choice;

    while (1) {
        printf("\n=====================================================\n");
        printf("           CS509 - COMMON ASSIGNMENT WRAPPER          \n");
        printf("=====================================================\n");
        printf("  1. Assignment 1 (GEMM Simple, GEMM Blocking, CSR Graph)\n");
        printf("  2. Assignment 2 (Coming Soon)\n");
        printf("  3. Assignment 3 (Coming Soon)\n");
        printf("  4. Exit\n");
        printf("-----------------------------------------------------\n");
        printf("Select Assignment to run (1-4): ");

        if (scanf("%d", &assignment_choice) != 1) {
            clear_input_buffer();
            printf("Invalid input. Please enter a valid choice.\n");
            continue;
        }

        switch (assignment_choice) {
            case 1:
                run_assignment_1_menu();
                break;
            case 2:
                printf("\n[Notice] Assignment 2 is not yet implemented.\n");
                break;
            case 3:
                printf("\n[Notice] Assignment 3 is not yet implemented.\n");
                break;
            case 4:
                printf("Exiting runner framework. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please choose 1-4.\n");
        }
    }

    return 0;
}