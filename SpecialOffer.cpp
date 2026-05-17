/*
Class: SpecialOffer
Inherited from: MenuItem

Purpose:
Represents a non-food, non-drink menu entry such as a gift card,
discount coupon, or promotional voucher. These items have a name
and a price (which may be 0.0), but they are never "prepared" in
the kitchen or at the bar.

Implementation requirements:
1. Constructor: Accept (const std::string& name, double price) and
   forward them to the MenuItem base-class constructor.
2. clone()  [Prototype pattern]
   Must return a heap-allocated deep copy of this object: return 
   new SpecialOffer(*this);
3. prepare()  [polymorphic virtual method]
    Must throw NotImplementedException unconditionally, because 
    special offers are neither cooked nor poured: throw NotImplementedException();
    Do NOT return any string — the exception is the entire body.
*/
