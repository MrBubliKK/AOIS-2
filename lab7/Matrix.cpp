#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Matrix {
private:
    vector<vector<int>> word_matrix;

public:

    void fill_word_matrix() {
        for (int i = 0; i < 16; i++) {
            vector<int> new_vec(16, 0);
            word_matrix.push_back(new_vec);
        }
    }

    vector<vector<int>> get_word_matrix() {
        return word_matrix;
    }

    void print_word_matrix() {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                cout << word_matrix[j][i] << " ";
            }
            cout << endl;
        }
    }

    bool add_word_in_matrix(int pos, vector<int> new_word) {
        if ((pos < 0) || (pos > 15) || (new_word.size() != 16)) {
            return false;
        }
        else {
            for (int i = 0; i < 16; i++) {
                if (i < pos) {
                    word_matrix[pos][i] = new_word[15 - pos + i +1];
                }
                else {
                    word_matrix[pos][i] = new_word[i - pos];
                }
            }
            return true;
        }
    }

    vector<int> find_word(int num) {
        vector<int> temp_el_list;
        vector<int> result_list;

        for (int i = 0; i < 16; i++) {
            if (i < num) {
                temp_el_list.push_back(word_matrix[num][i]);
            }
            else {
                result_list.push_back(word_matrix[num][i]);
            }
        }

        for (int i = 0; i < temp_el_list.size(); i++) {
            result_list.push_back(temp_el_list[i]);
        }
        return result_list;
    }

    vector<int> find_adress_column(int num) {
        vector<int> result_list;
        int el_pos = num;
        int x_pos = 0;
        while (el_pos < 16) {
            result_list.push_back(word_matrix[x_pos][el_pos]);
            el_pos++;
            x_pos++;
        }
        el_pos = 0;

        for (int i = 16 - num; i < 16; i++) {
            result_list.push_back(word_matrix[i][el_pos]);
            el_pos++;
        }
        return result_list;
    }

    void make_f1(int num_word, int num_column, int matrix_pos) {
        vector<int> list_of_word = find_word(num_word);
        vector<int> list_of_adress_column = find_adress_column(num_column);
        vector<int> result_list = {};

        for (int i = 0; i < list_of_word.size(); i++) {
            if ((list_of_word[i] == 1) && (list_of_adress_column[i] == 1)) {
                result_list.push_back(1);
            }
            else {
                result_list.push_back(0);
            }
        }

        add_word_in_matrix(matrix_pos, result_list);

    }

    void make_f3(int num_word, int num_column, int matrix_pos) {
        vector<int> list_of_word = find_word(num_word);
        vector<int> list_of_adress_column = find_adress_column(num_column);
        vector<int> result_list = {};

        for (int i = 0; i < list_of_word.size(); i++) {
            if (list_of_word[i] == 1) {
                result_list.push_back(1);
            }
            else {
                result_list.push_back(0);
            }
        }

        add_word_in_matrix(matrix_pos, result_list);
    }

    void make_f12(int num_word, int num_column, int matrix_pos) {
        vector<int> list_of_word = find_word(num_word);
        vector<int> list_of_adress_column = find_adress_column(num_column);
        vector<int> result_list = {};

        for (int i = 0; i < list_of_word.size(); i++) {
            if (list_of_word[i] == 1) {
                result_list.push_back(0);
            }
            else {
                result_list.push_back(1);
            }
        }

        add_word_in_matrix(matrix_pos, result_list);
    }

    void make_f14(int num_word, int num_column, int matrix_pos) {
        vector<int> list_of_word = find_word(num_word);
        vector<int> list_of_adress_column = find_adress_column(num_column);
        vector<int> result_list = {};

        for (int i = 0; i < list_of_word.size(); i++) {
            if ((list_of_word[i] == 1) && (list_of_adress_column[i] == 1)) {
                result_list.push_back(0);
            }
            else {
                result_list.push_back(1);
            }
        }

        add_word_in_matrix(matrix_pos, result_list);
    }

    //Упрощает функцию подсчета суммы
    bool sum_numbers_check_sign(vector<int> first, vector<int> second, vector<int>* sum_mas, int add_num) {
        for (int i = 0; i < first.size(); i++) {
            if ((first[i] == 0) && (second[i] == 0)) {
                if (add_num >= 3) {
                    sum_mas->push_back(1);
                    add_num -= 2;
                }
                else if (add_num == 2) {
                    sum_mas->push_back(0);
                    add_num--;
                }
                else if (add_num == 1) {
                    sum_mas->push_back(1);
                    add_num--;
                }
                else {
                    sum_mas->push_back(0);
                }
            }
            else if ((first[i] == 1) && (second[i] == 1)) {
                if (add_num >= 1) {
                    sum_mas->push_back(1);
                }
                else {
                    sum_mas->push_back(0);
                    add_num++;
                }
            }
            else {
                if (add_num >= 2) {
                    sum_mas->push_back(1);
                    add_num--;
                }
                else if (add_num == 1) {
                    sum_mas->push_back(0);
                }
                else {
                    sum_mas->push_back(1);
                }
            }
        }

        while (add_num > 0) {
            if (add_num >= 2) {
                sum_mas->push_back(0);
                add_num--;
            }
            else if (add_num == 1) {
                sum_mas->push_back(1);
                add_num--;
            }
        }
        return true;
    }

    //Суммирует два целых числа
    vector<int> sum_numbers(vector<int> first, vector<int> second) {
        int add_num = 0;
        vector<int> sum_mas;
        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());

        sum_numbers_check_sign(first, second, &sum_mas, add_num);

        reverse(sum_mas.begin(), sum_mas.end());
        return sum_mas;
    }

    //Находит все слова с заданным V и складывает их A B части
    bool find_all_words_V(string inp_V) {
        vector<int> word_list;
        int count = 0;
        for (int i = 0; i < 16; i++) {
            string word_V = "";
            for (int j = 0; j < 3; j++) {
                if (i + j < 16) {
                    word_V += to_string(word_matrix[i][i + j]);
                }
                else {
                    word_V += to_string(word_matrix[i][j - 1]);
                }
            }
            if (inp_V == word_V) {
                word_list = find_word(i);
                word_list = sum_V(word_list, i);
                add_word_in_matrix(i, word_list);
                count++;
            }
        }
        
        if (count > 0) {
            return true;
        }
        else {
            return false;
        }
    }

    vector<int> sum_V(vector<int> word_list, int pos) {
        vector<int> list_A = {};
        vector<int> list_B = {};

        for (int j = 0; j < 4; j++) {
            list_A.push_back(word_list[j + 3]);
            list_B.push_back(word_list[j + 7]);
        }
        vector<int> list_sum_numbers = sum_numbers(list_A, list_B);
                
        while (list_sum_numbers.size() < 5) {
            reverse(list_sum_numbers.begin(), list_sum_numbers.end());
            list_sum_numbers.push_back(0);
            reverse(list_sum_numbers.begin(), list_sum_numbers.end());

        }

        for (int j = 0; j < list_sum_numbers.size(); j++) {
            word_list[j + 11] = list_sum_numbers[j];
        }

        return word_list;
    }

    string transfer_10_to_2(int temp_decimal_number) {
        int decimal_number = temp_decimal_number;
        string binary_number = "";

        while (decimal_number != 0) {
            binary_number += to_string(abs(decimal_number % 2));
            decimal_number /= 2;
        }
        reverse(binary_number.begin(), binary_number.end());
        return binary_number;
    }

    int transfer_2_to_10(string temp_binary_number) {
        int decimal_number = 0;
        string binary_number = temp_binary_number;
        reverse(binary_number.begin(), binary_number.end());


        for (int i = 0; i < binary_number.size(); i++) {
            decimal_number += (binary_number[i] - '0') * pow(2, i);
        }

        return decimal_number;
    }
    
    vector<int> find_min_word(vector<int> inp_word) {
        string string_inp_word = "";

        vector<int> min_word = inp_word;
        string min_string_word = "";

        for (int j = 0; j < min_word.size(); j++) {
            min_string_word += to_string(min_word[j]);
        }

        string_inp_word = min_string_word;
        int min_int_word = transfer_2_to_10(min_string_word);
        int int_inp_word = min_int_word;
        int delta = 1000000;

        for (int i = 0; i < word_matrix.size(); i++) {

            vector<int> temp_word = find_word(i);
            string temp_string_word = "";

            for (int j = 0; j < temp_word.size(); j++) {
                temp_string_word += to_string(temp_word[j]);
            }

            int temp_int_word = transfer_2_to_10(temp_string_word);
            int delta_temp = int_inp_word - temp_int_word;

            if ((temp_int_word <= int_inp_word) && (delta_temp < delta)) {
                min_int_word = temp_int_word;
                min_word = temp_word;
                delta = delta_temp;
            }

        }
        return min_word;
    }

    vector<int> find_max_word(vector<int> inp_word) {
        string string_inp_word = "";

        vector<int> max_word = inp_word;
        string max_string_word = "";

        for (int j = 0; j < max_word.size(); j++) {
            max_string_word += to_string(max_word[j]);
        }

        string_inp_word = max_string_word;
        int max_int_word = transfer_2_to_10(max_string_word);
        int int_inp_word = max_int_word;
        int delta = 1000000;

        for (int i = 0; i < word_matrix.size(); i++) {

            vector<int> temp_word = find_word(i);
            string temp_string_word = "";

            for (int j = 0; j < temp_word.size(); j++) {
                temp_string_word += to_string(temp_word[j]);
            }

            int temp_int_word = transfer_2_to_10(temp_string_word);
            int delta_temp = temp_int_word - int_inp_word;

            if ((temp_int_word >= int_inp_word) && (delta_temp < delta)) {
                max_int_word = temp_int_word;
                max_word = temp_word;
                delta = delta_temp;
            }

        }
        return max_word;
    }

    int calculate_g_formula(int next_g, int a, int S, int l) {
        int first_part;

        if ((a == 1) && (S == 1) && (l == 1)) {
            first_part = 1;
        }
        else {
            first_part = 0;
        }

        if ((next_g == 1) || (first_part == 1)) {
            return 1;
        }
        else {
            return 0;
        }
    }

    int calculate_l_formula(int next_l, int a, int S, int g) {
        int first_part;

        if ((a == 1) && (S == 1) && (g == 1)) {
            first_part = 1;
        }
        else {
            first_part = 0;
        }

        if ((next_l == 1) || (first_part == 1)) {
            return 1;
        }
        else {
            return 0;
        }
    }

    int make_reverse_sign(int num) {
        if (num == 0) {
            return 1;
        }
        else if (num == 1) {
            return 0;
        }
    }

    int calculate_final_g_l(vector<int> inp_word, vector<int> find_word) {
        reverse(inp_word.begin(), inp_word.end());
        reverse(find_word.begin(), find_word.end());

        int g = 0;
        int S = 0;
        int a = 0;
        int l = 0;
        int next_g = 0;
        int next_l = 0;

        for (int i = 15; i >= 0; i--) {
            a = inp_word[i];
            S = find_word[i];
            if ((i + 1) > 15) {
                next_l = 0;
                next_g = 0;
            }
            else {
                next_g = g;
                next_l = l;
            }
            g = calculate_g_formula(next_g, make_reverse_sign(a), S, make_reverse_sign(next_l));
            l = calculate_l_formula(next_l, a, make_reverse_sign(S), make_reverse_sign(next_g));
        }

        if (g == l) {
            return 1;
        }
        else if (g > l) {
            return 2;
        }
        else {
            return 3;
        }

    }

    void compare_min_word(vector<int> inp_word) {
        cout << "Сравнение с минимальным элементом:\n";
        vector<int> min_word = find_min_word(inp_word);
        int result = calculate_final_g_l(inp_word, min_word);
        if (result == 1) {
            cout << "S = A\n";
        }
        else if (result == 2) {
            cout << "S > A\n";
        }
        else {
            cout << "S < A\n";
        }
    }

    void compare_max_word(vector<int> inp_word) {
        cout << "Сравнение с максимальным элементом:\n";
        vector<int> max_word = find_max_word(inp_word);
        int result = calculate_final_g_l(inp_word, max_word);
        if (result == 1) {
            cout << "S = A\n";
        }
        else if (result == 2) {
            cout << "S > A\n";
        }
        else {
            cout << "S < A\n";
        }
    }

    bool add_adress_column(int pos, vector<int> column_list) {
        if ((pos < 0) || (pos > 15) || column_list.size() != 16) {
            return false;
        }
        for (int i = 0; i < 16; i++) {
            if (pos + i > 15) {
                word_matrix[i][15 - pos + 1] = column_list[i];
            }
            else {
                word_matrix[i][pos + i] = column_list[i];
            }
        }
        return true;
    }
};