#include <bits/stdc++.h>

using namespace std;

struct recipe{
    string name;
    vector<string> ingredients;
};

struct category{
    set<string> all_ingredients;
    vector<recipe> all_recipes;
};

map<string, category> categories;

void enter_data();
void pick_category(string &choice);
void search_for_meals(string choice);


int main()
{

    enter_data();

    string choice;
    pick_category(choice);

    search_for_meals(choice);


    return 0;
}



void enter_data(){

    ifstream fin("Meals.txt");

    int number_of_categories;
    fin >> number_of_categories;

    for(int j=1; j<=number_of_categories; j++){
        vector<recipe> recipes_in_category;
        set<string> ingredients_in_category;

        string cat;
        getline(fin, cat);
        getline(fin, cat);
        getline(fin, cat);

        int number_of_recipes;
        fin >> number_of_recipes;

        for(int k=1; k<=number_of_recipes; k++){
            vector<string> new_recipe;

            string recipe_name;
            getline(fin, recipe_name);
            getline(fin, recipe_name);

            int number_of_ingredients;
            fin >> number_of_ingredients;

            for(int l=1; l<=number_of_ingredients; l++){
                string ingr;
                fin >> ingr;
                new_recipe.push_back(ingr);
                ingredients_in_category.insert(ingr);
            }

            recipe r;
            r.name=recipe_name;
            r.ingredients=new_recipe;

            recipes_in_category.push_back(r);
        }
        category new_category;
        new_category.all_ingredients=ingredients_in_category;
        new_category.all_recipes=recipes_in_category;

        categories.insert({cat, new_category});
    }
}


void pick_category(string &choice){
    cout << "Categories of meals:" << endl;

    for(auto c:categories){
        cout << "* " << c.first << endl;
    }

    cout << "Enter a category: " << endl;
    cin >> choice;
}

void search_for_meals(string choice){
    bool found=false;

    for(auto c:categories){
        if(choice==c.first){
            found=true;

            set<string> have;
            for(auto e:c.second.all_ingredients){
                cout << "Do you have " << e << "?" << endl;
                string answer;
                cin >> answer;

                if(answer=="yes" || answer=="Yes"){
                    have.insert(e);
                }
            }

            int printed=0;

            for(recipe rec:c.second.all_recipes){
                int cnt=0, to_compare=0;
                for(auto in:rec.ingredients){
                    to_compare++;
                    if(have.find(in)!=have.end()) cnt++;
                }
                if(cnt+1>=to_compare){
                    cout << rec.name << endl;
                    printed++;
                }
            }
            if(printed==0) cout << "Sorry, go google some recipes." << endl;
        }
    }
    if(found==false) cout << "Wrong category" << endl;
}
