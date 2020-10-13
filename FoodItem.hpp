#ifndef FOODITEM_H
#define FOODITEM_H

class FoodItem: public Resource
{


FoodItem(double weight, double volume)
{
  this.weight = weight;
  this.volume = volume;
  wearFactor = 0;
  wear = 1;
}

FoodItem(const FoodItem & foodItem)
{

  weight = foodItem.weight;
  volume = foodItem.volume;
  wearFactor = 0;
  wear = 1;

}

};

#endif
