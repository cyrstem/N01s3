#include "VisualSystem.h"
//--------------------------------------------------------------
VisualSystem::VisualSystem(){
    //FBOS
    ofFboSettings s;
    s.width=ofGetWidth();
    s.height= ofGetHeight();
    s.internalformat =GL_RGBA;
    s.useDepth = true;
    s.useStencil = false;
    s.numSamples = 12;

    fbo.allocate(s);

    fbo.begin();
        ofClear(0);
    fbo.end();


     //------camera stafff
    centro = glm::vec3(0,0,0);
    cam.lookAt(centro);
    cam.setPosition(glm::vec3(0,0,2200));


    //sphere.set(00,12);

    ico_sphere = ofIcoSpherePrimitive(500,2);
    spinX +=10;

 }
 //--------------------------------------------------------------
void VisualSystem::enviroment(){
           //lights
    ambient.setAmbientColor(ofFloatColor(ofColor::whiteSmoke));
    ambient.setPosition(0,0,0);
    ambient.setScale(20);

    spot.setPointLight();
    spot.setPosition(0,0,100);
    spot.setDiffuseColor(ofFloatColor(255,255,122));
    spot.setSpecularColor(ofFloatColor(255,255,155));
    spot.setSpotConcentration(45);
    spot.setSpotlightCutOff(50);
    spot.enable();



    areaLight.setup();
    areaLight.enable();
    areaLight.setAreaLight(1500,1500);
    areaLight.setAmbientColor(ofFloatColor(1.0,0.1,0.1));
    areaLight.setAttenuation(1.0,1.0001,0.0001);
    areaLight.setDiffuseColor(ofFloatColor(1,1,1));
    areaLight.setSpecularColor(ofFloatColor(1,0,1));
    areaLight.rotateDeg(0,glm::vec3(1,0,0));
    areaLight.rotateDeg(-45,glm::vec3(1,0,0));
    areaLight.setPosition(0,150,-100);


    material.setAmbientColor(ofFloatColor(0.1,0.1,0.1,1.0));
	material.setDiffuseColor(ofFloatColor(0.8,0.8,0.8,1.0));
	material.setSpecularColor(ofFloatColor(0.8,0.8,0.8,1.0));
	material.setShininess(10);
}

 //--------------------------------------------------------------
 void VisualSystem::scene(){
     // vertices = sphere.getMesh().getVertices();
       vertices = ico_sphere.getMesh().getVertices();
       //ico_sphere.rotate(spinX,0.0,1.0,0.0);

     // this part is for controling born rate of the particle  still neeed  to work 
    // it seems  to  work but not  for the aplication  as i  first imagine 

      //glm::vec3 force(ofRandom(-5.0,5.0),ofRandom(-5.1,5.0),ofRandom(-5.1,5.1));

   glm::vec3 force(ofRandom(-0.005,0.005),ofRandom(-0.005,0.005),ofRandom(-0.005,0.005));


    for (int i = 0; i < vertices.size(); i++)
    {
        glm::vec3 v = vertices[i];
        if(ofGetFrameNum() % 60  == 0){
            Particle pTemp;
            pTemp.pos = v + ofPoint(0,0,0);
            pTemp.rotate += ofRandom(0,180);
           // pTemp.applyForce(force);
            p.push_back(pTemp);
        }
    }




   
    fbo.begin();
        cam.begin();
        ambient.enable();


        //here goes the markers 

for (int x = -1  ; x <= 1; x+=2)
   {
       for (int y = -1; y <=1; y+=2)
       {
           for (int z = -1; z < 1; z+=2)
           {
               ofPushStyle();
               ofSetColor(ofColor::red);
               drawCorner(ofPoint(x*(1500/2+10),y*(1500/2+10),z*(10+10)));
               ofPopStyle();
           }
           
       }
       
   }

   // sphere.drawWireframe();
   //ico_sphere.drawVertices();
   //ico_sphere.setPosition(100,0,0);
   //ico_sphere.setPosition(ofGetMouseX(),ofGetMouseY(),0);
//    sphere.drawWireframe();
//    sphere.setPosition(ofGetMouseX(),ofGetMouseY(),0);



    for (int i = 0; i < p.size(); i++)
        {   
             material.begin();  
             p[i].draw();
             material.end();
            if ( p[i].dead == true)
            {
                p.erase(p.begin()); 
            }
         
        }
    


    //areaLight.draw();
    //ambient.draw();
    //spot.draw();


        cam.end();
    
        fbo.end();
 }

 //--------------------------------------------------------------
 void VisualSystem::show(){
       reset();
        scene();
        fbo.draw(0,0);
 
 }
//--------------------------------------------------------------
void VisualSystem::reset(){
   fbo.begin();
        ofClear(0);
        fbo.end();


          for (int i = 0; i < p.size(); i++)
        {
            p[i].update();
        }  
}
//--------------------------------------------------------------
void VisualSystem::drawCorner(ofPoint p){
    float pl = 100.0;
    ofDrawLine(p.x,p.y,p.z,p.x,p.y,p.z -sin(p.z)*pl);
    ofDrawLine(p.x,p.y,p.z,p.x,p.y-sin(p.z)*pl,p.z);
    ofDrawLine(p.x,p.y,p.z,p.x-sin(p.z)*pl,p.y,p.z);
}