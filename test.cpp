for (int i = 0; i < car_bag.getCurrentSize(); ++i)
{
    cout << "*\n";
    first->getItem().print();
    cout << "*\n";
    first = first->getNext();
}