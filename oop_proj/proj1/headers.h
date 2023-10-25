#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Class for managing user interactions & menu navigation
class Greeter {
public:
    Greeter() {};

    // Display the main menu options for the user
    void printOption();

    // Select an option to navigate to the corresponding feature
    void selectOption();

    // View the database of recipes
    void showRecipe();

    // Search for a specific recipe
    void searchRecipe();

    // Add a new recipe to the database
    void addRecipe();

    // Remove a recipe from the database
    void deleteRecipe();

    // View the meal plans
    void showPlan();

    // Search for existing meal plans
    void searchPlan();

    // Create a new meal plan
    void addPlan();

    // Delete a meal plan
    void deletePlan();
};

// Class to represent an ingredient
class Ingredient {
private:
    std::string name;  // Name of the ingredient
    int quantity;      // Quantity of the ingredient

public:
    Ingredient(const std::string& ingredient, int quantity);

    // Set the name of the ingredient
    void setName(const std::string& ingredient);

    // Get the name
    std::string getName() const;

    // Set quantity
    void setQuantity(int quantity);

    // Get quantity
    int getQuantity() const;
};

// Class to represent a Recipe
class Recipe {
private:
    std::string name;                          // Recipe's name
    std::map<Ingredient, int> ingredients; // Recipe's ingredients & amounts
    std::string annotation;                   // Recipe's description

public:
    Recipe();

    Recipe(const std::string& recipeName, const std::map<Ingredient, int>& ingredients, const std::string& annotation);

    // Set the name of the recipe
    void setName(const std::string& name);

    // Get the name
    std::string getName() const;

    // Set ingredients and their quantities
    void setIngredients(const std::map<Ingredient, int>& ingredients);

    // Get ingredients and their quantities
    std::map<Ingredient, int> getIngredients() const;

    // Edit recipe information (name, ingredients, annotation)
    void editRecipeInformation();

    // Print recipe information
    void printRecipe();
};

// Class to manage the Recipe database
class RecipeDB {
private:
    std::vector<Recipe> recipes;

public:
    RecipeDB();

    // Get a list of all recipes in the database
    std::vector<Recipe> getAllRecipes() const;

    // Search recipes in the database
    void searchRecipe();

    // Show the database of recipes
    void showRecipe();

    // Add a new recipe to the database
    void addRecipe(const Recipe& recipe);

    // Remove a recipe from the database
    void deleteRecipe(const Recipe& recipe);

    // Edit some contents of a recipe
    void editRecipe(const Recipe& recipe);
};

// Class to represent a Meal
class Meal {
private:
    std::vector<Recipe> recipes;
    std::string name;
    int numPeople;

public:
    Meal(std::string mealTitle = "", int numPeople = 1);

    // Display meal information
    void printMeal();

    // Set the name of the meal
    void setName(const std::string& mealName);

    // Get the name of the meal
    std::string getName() const;

    // Set the number of people for the meal
    void setNumPeople(int numPeople);

    // Get the number of people for the meal
    int getNumPeople() const;
};

// Class to represent a Date
class Date {
private:
    int year, month, day;
    std::string event; // Anniversary or any event of the date
    std::vector<Meal> meals;

public:
    Date();

    Date(int year, int month, int day, std::string event = "");

    // Get Date, Event, and Meals
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    std::string getEvent() const { return event; }
    std::vector<Meal> getMeals() const { return meals; }

    // Edit meals for the date
    void editMeal();
};

// Class to manage Meal Plans
class PlanManager {
private:
    std::vector<Date> plans;

public:
    PlanManager();

    // Search a meal plan
    void searchPlan();

    // Display a list of meal plans
    void showPlan();

    // Create a new meal plan
    void addPlan();

    // Delete a meal plan
    void deletePlan();

    // Edit an existing meal plan
    void editExistingPlan();

    // Add a recipe to a specific meal on a given date
    void addRecipeToMeal(const Date& date, const Meal& meal, const Recipe& recipe);

    // Remove a recipe from a specific meal on a given date
    void removeRecipeFromMeal(const Date& date, const Meal& meal, const Recipe& recipe);
};
