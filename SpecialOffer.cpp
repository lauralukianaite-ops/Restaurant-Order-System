/*
 Klasė: SpecialOffer
 Paveldima iš: MenuItem
 
 Tikslas: 
 Ši klasė skirta reprezentuoti specialius rinkinius ar nevalgomus/negaminamus 
 elementus (pvz. dovanų kuponus).
 
 Reikalavimai įgyvendinimui:
 1. Konstruktorius turi priimti (name, price) ir perduoti juos bazinei klasei.
 2. clone() metodas turi atlikti Prototype gilų kopijavimą: return new SpecialOffer(*this);
 3. prepare() metodas turi neturėti jokios realizacijos ir provalo 
    mesti 'NotImplementedException' išimtį, nes specialūs pasiūlymai
    nėra gaminami ar pilstomi.
 ============================================================================
*/
