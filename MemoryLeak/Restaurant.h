// Program: Restaurant
// Name: Inderjit Bassi
// Date: 6/13/14
// This holds the fields for reading in data, that are appropriate to a restaurant.
    
#ifndef  RESTAURANT_H_INCLUDED
#define RESTAURANT_H_INCLUDED

#include <string>
#include <iomanip>
#include <iostream>
    
using namespace std;

class Restaurant
{
private:
    string restaurant;      // String that holds the restaurant name
    string review;          // String that holds the review of the restaurant
    string foodType;        // String that holds the type of food at a restaurant
    string distance;        // String that holds the distance of the restaurant from De Anza College
	
	int numSearch;			// HONORS: Holds the most searched for items
        
public:

																
    Restaurant() {restaurant = "none"; foodType = "none"; review = "none"; distance = "none"; numSearch = 0;}	// Default constructor
	Restaurant(string n, string t, string r, string d, int num = 0) {restaurant=n; foodType=t; review = r; distance=d; numSearch = num;} // default constructor with 4 inputs arguments
     
    // Mutators
    void setRestaurant(string r)	{restaurant = r;} 
    void setReview(string s)		{review = s;}
    void setFoodType(string f)		{foodType = f;}
    void setDistance(string d)		{distance = d;}

	void updateSearch ()			{numSearch++;}	// Updates the search function
        
    // Getters
    string getRestaurant() const	{return restaurant;}
    string getReview() const		{return review;}
    string getFoodType() const		{return foodType;}
    string getDistance() const		{return distance;}

	int getNumSearch () const	{return numSearch;}	// Gets the number searched
    
    //Overloads
    bool operator > (const Restaurant &obj) const;
	
    bool operator < (const Restaurant &obj) const;
	
    bool operator == (const Restaurant&obj) const;
	
    
    void printKey() {cout <<left<<getRestaurant()<<endl;}	// Prints out the key (name)
    void printLayout() {cout << left << getRestaurant() << "," <<getFoodType()<<","<<getReview()<<","<<getDistance()<<endl;}	// Prints out the structure of restaurant class
    void printAll() {cout << "Name: " << getRestaurant() << endl << "Type: " << getFoodType() << endl << "Review: " << getReview() << endl << "Distance: " << getDistance() << endl << "Searching times: " << getNumSearch() << endl;}
	// prints out everything
};
#endif