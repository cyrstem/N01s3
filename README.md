# N01s3

#
For those who still remenber the old days of winamp ,sonique  and music  i
build this simple audio player with visuals 
it only lets you load one song at the time so you can sit and enjoy  the graphics  generated 
and the song 
#
something to use later on 
 'this solution where not apply   but it might be usefull later 



    auto it = max_element(std::begin(lfh),std::end(lfh));
    auto it2 = min_element(std::begin(lfh),std::end(lfh));


    // cout<<*it<<endl;
    // cout<<*it2<<endl;
    float a =*it; 
    float b =*it2; 
    float incre = 1.3;
    fX = a;
    fY = b;
    fZ = ofLerp(a,b,incre);
    '