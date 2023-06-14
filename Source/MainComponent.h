#pragma once

#include <JuceHeader.h>
#include <vector>
#include <set>
#include "checkAlgorithm.h"

const int CoordY[26] = {281,273,265,256,248,239,231,223,214,206,198,189,182,129,122,114,105,97,88,80,72,63,55,47,38,31};
const int tone_in_C[26] = {16,17,19,21,23,24,26,28,29,31,33,35,36,36,38,40,41,43,45,47,48,50,52,53,55,57};
int tone_to_change_of_all[7][4] = {{1,8,16,23},{5,12,13,20},{2,9,17,24},{6,14,21,-1},{3,10,18,25},{0,7,15,22},{4,11,19,-1}};
const int order_in_sharp[7] = {0,1,2,3,4,5,6};
const int order_in_flat[7] = {1,5,4,3,2,1,0};
const int sharp_signature_distance[7] = {0,26,-5,17,43,9,33};
const int flat_signature_distance[7] = {0,-26,7,-17,17,-9,24};
int tone[26][4];
const float note_size = 25.0f;
const float symbol_size = 1.5*note_size;
const float accidental_size = 39.0f;
const float staff_size = 350.0f;

int tonality = 0;
int noteChosen = -1;
int sf,nt;
set<pair<int,int>> marked_note;



//==============================================================================
//取得当前调对应音高
void get_tones_now()
{
    for(int i=0;i<26;i++)tone[i][3]=tone_in_C[i];
    vector<int>tone_to_change;
    
    if(tonality==0)return;
    
    for(int i=0;i<abs(tonality);i++)
    {
        for(int j=0;j<4;j++)
        {
            if(tone_to_change_of_all[i][j]==-1)continue;
            tone_to_change.push_back(tone_to_change_of_all[i][j]);
        }
    }
    
    if(tonality>0)
    {
        for(auto v : tone_to_change)tone[v][3]++;
    }
    else if(tonality<0)
    {
        for(auto v : tone_to_change)tone[v][3]--;
    }
    return;
}


class release_zoneComponent : public juce::Component
{
public:
    release_zoneComponent(MouseListener *Parent)
    {
        addMouseListener(Parent, false);
    }
    ~release_zoneComponent(){}
    
    void paint(juce::Graphics &g)override
    {
 
    }
    void resized()override
    {}
    
    void mouseDown(const juce::MouseEvent &event)override
    {
        noteChosen = -1;
    }
    
private:
};


class tone_textComponent : public juce::Component
{
public:
    tone_textComponent(int startTone) : toneToShow(startTone)
    {}
    ~tone_textComponent(){}
    
    void paint(juce::Graphics &g)override
    {
        g.setFont(20.0f);
        g.drawText(std::to_string(toneToShow), getLocalBounds(),juce::Justification::centred,true);
    }
    
    void resized() override
    {}
    
    int toneToShow;

private:
    
};

class check_textComponent : public juce::Component
{
public:
    check_textComponent(std::string startText) : textToShow(startText)
    {}
    ~check_textComponent(){}
    
    void paint(juce::Graphics &g)override
    {
        g.setFont(20.0f);
        g.setOpacity(Opa);
        g.drawText(textToShow, getLocalBounds(),juce::Justification::centredTop,true);
    }
    
    void resized() override
    {}
    
    std::string textToShow;
    float Opa = 0.3f;

private:
    
};


class lineComponent : public juce::Component
{
public:
    lineComponent(){}
    ~lineComponent(){}
    
    void paint(juce:: Graphics &g) override
    {
        g.setColour(juce::Colours::black);
        g.drawLine(startX,12,endX,12,3);
    }
    
    void resized() override
    {}
    int startX = 2.0f;
    int endX = 40.0f;
    
private:
};


class noteGraphComponent : public juce::Component
{
public:
    noteGraphComponent(){}
    ~noteGraphComponent(){}
    
    void paint(juce::Graphics &g) override
    {
        if(isChosen)
        {
            note_chosen->drawWithin(g, juce::Rectangle<float>(note_size,note_size), juce::RectanglePlacement::Flags::centred, 1.0f);
        }
        else
        {
            if(isMarked)
            {
                note_marked->drawWithin(g, juce::Rectangle<float>(note_size,note_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
            else
            {
                note->drawWithin(g, juce::Rectangle<float>(note_size,note_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
        }
    }
    
    
    void resized() override
    {}
    
    
    bool isChosen = false;
    bool isMarked = false;
    
private:
    std::unique_ptr<juce::Drawable>note = juce::Drawable::createFromImageData(BinaryData::note_svg,BinaryData::note_svgSize);
    std::unique_ptr<juce::Drawable>note_chosen = juce::Drawable::createFromImageData(BinaryData::note_chosen_svg,BinaryData::note_chosen_svgSize);
    std::unique_ptr<juce::Drawable>note_marked = juce::Drawable::createFromImageData(BinaryData::note_marked_svg,BinaryData::note_marked_svgSize);
};

class naturalComponent : public juce::Component
{
public:
    naturalComponent(){}
    ~naturalComponent(){}
    
    void paint(juce::Graphics &g) override
    {
        if(isChosen)
        {
            natural_chosen->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
        }
        else
        {
            if(isMarked)
            {
                natural_marked->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
            else
            {
                natural->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
        }
    }
    
    void resized() override
    {}
    
    bool isChosen = false;
    bool isMarked = false;
    
private:
    std::unique_ptr<juce::Drawable>natural = juce::Drawable::createFromImageData(BinaryData::natural_svg,BinaryData::natural_svgSize);
    std::unique_ptr<juce::Drawable>natural_chosen = juce::Drawable::createFromImageData(BinaryData::natural_chosen_svg,BinaryData::natural_chosen_svgSize);
    std::unique_ptr<juce::Drawable>natural_marked = juce::Drawable::createFromImageData(BinaryData::natural_marked_svg,BinaryData::natural_marked_svgSize);
};




class flatComponent : public juce::Component
{
public:
    flatComponent(){}
    ~flatComponent(){}
    
    void paint(juce::Graphics &g) override
    {
        if(isChosen)
        {
            flat_chosen->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
        }
        else
        {
            if(isMarked)
            {
                flat_marked->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
            else
            {
                flat->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
        }
    }
    
    void resized() override
    {}
    
    bool isChosen = false;
    bool isMarked = false;
    
private:
    std::unique_ptr<juce::Drawable>flat = juce::Drawable::createFromImageData(BinaryData::flat_svg,BinaryData::flat_svgSize);
    std::unique_ptr<juce::Drawable>flat_chosen = juce::Drawable::createFromImageData(BinaryData::flat_chosen_svg,BinaryData::flat_chosen_svgSize);
    std::unique_ptr<juce::Drawable>flat_marked = juce::Drawable::createFromImageData(BinaryData::flat_marked_svg,BinaryData::flat_marked_svgSize);
};




class sharpComponent : public juce::Component
{
public:
    sharpComponent(){}
    ~sharpComponent(){}
    
    void paint(juce::Graphics& g) override
    {
        if(isChosen)
        {
            sharp_chosen->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
        }
        else
        {
            if(isMarked)
            {
                sharp_marked->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
            else
            {
                sharp->drawWithin(g, juce::Rectangle<float>(symbol_size,symbol_size), juce::RectanglePlacement::Flags::centred, 1.0f);
            }
        }
    }
    
    void resized() override
    {
        
    }
    
    bool isChosen = false;
    bool isMarked = false;
private:
    std::unique_ptr<juce::Drawable>sharp = juce::Drawable::createFromImageData(BinaryData::sharp_svg,BinaryData::sharp_svgSize);
    std::unique_ptr<juce::Drawable>sharp_chosen = juce::Drawable::createFromImageData(BinaryData::sharp_chosen_svg,BinaryData::sharp_chosen_svgSize);
    std::unique_ptr<juce::Drawable>sharp_marked = juce::Drawable::createFromImageData(BinaryData::sharp_marked_svg,BinaryData::sharp_marked_svgSize);
};







class accidentalComponent: public juce::Component
{
public:
    accidentalComponent()
    {
        addChildComponent(flat);
        addChildComponent(sharp);
        addChildComponent(natural);
    }
    ~accidentalComponent(){}
    
    void paint(juce::Graphics &g) override
    {
    }
    
    void resized() override
    {
        natural.setBounds(0, 7,accidental_size,accidental_size);
        sharp.setBounds(-2, 7,accidental_size,accidental_size);
        flat.setBounds(-2,-2,accidental_size,accidental_size);
    }
    
    naturalComponent natural;
    sharpComponent sharp;
    flatComponent flat;
};



class noteComponent : public juce::Component
{
public:
    noteComponent()
    {
        addAndMakeVisible(noteGraph);
        addAndMakeVisible(accidental);
        addChildComponent(line);
        accidental.toBack();
    }
    ~noteComponent(){}
    
    void paint(juce::Graphics& g) override
    {
    }
    
    void resized() override
    {
        noteGraph.setBounds(35,14,note_size,note_size);
        accidental.setBounds(10,0,accidental_size-10,accidental_size+10);
        line.setBounds(26,14,50,50);
        line.toBack();
    }
    
    
    
    
    int accidentalFlag = 3;
    
    accidentalComponent accidental;
    noteGraphComponent noteGraph;
    lineComponent line;
private:
    
};


class check_zoneComponent : public juce::Component
{
public:
    check_zoneComponent(noteComponent *note_input,Component *Parent,int s,int n) : note(note_input),staff_now(s),note_now(n)
    {
        addMouseListener(Parent, false);
    }
    ~check_zoneComponent(){}
    
    void paint(juce::Graphics &g)override
    {
      
    }
    
    void resized()override
    {
        
    }
    
    void mouseDown(const juce::MouseEvent &event)override
    {
        noteChosen = staff_now*4+note_now;
        sf = staff_now;
        nt = note_now;
    }
    
    
private:
    noteComponent *note;
    int staff_now;
    int note_now;
};
    

//==============================================================================

class staffComponent : public juce::Component
{
public:
    
    staffComponent(int s,staffComponent *opposite) : staff_now(s),release_zone(this),oppo_staff(opposite)
    {
        for(int i=0;i<4;i++)
        {
            addAndMakeVisible(note[i]);
            addAndMakeVisible(check_zone[i]);
           
        }
        addAndMakeVisible(release_zone);
        for(int i=0;i<7;i++)for(int j=0;j<2;j++)
        {
            addChildComponent(sharpSign[i][j]);
            addChildComponent(flatSign[i][j]);
        }
    }
    ~staffComponent(){}
    

    
    void paint(juce::Graphics& g) override
    {
        staff->drawWithin(g, juce::Rectangle<float>(staff_size,staff_size), juce::RectanglePlacement::Flags::centred, 1.0f);
    }
    

    void resized() override
    {
        for(int i=0;i<4;i++)
        {
            note[i].setBounds(225,CoordY[pos[i]],3*note_size,2*note_size-5);
            tone_text[i].setBounds(30+i*30,0,50,50);
            check_zone[i].setBounds(260,CoordY[pos[i]]+14,note_size,note_size);
            check_zone[i].toFront(true);
            note[i].toBack();
        }
        release_zone.setBounds(0, 0, 450, 400);
        
        for(int i=0;i<7;i++)
        {
            sharpSign[i][0].setBounds(88+i*12,54+sharp_signature_distance[i],accidental_size,accidental_size);
            sharpSign[i][1].setBounds(88+i*12, 222+sharp_signature_distance[i], accidental_size, accidental_size);
            flatSign[i][0].setBounds(88+i*12,79+flat_signature_distance[i],accidental_size,accidental_size);
            flatSign[i][1].setBounds(88+i*12, 247+flat_signature_distance[i], accidental_size, accidental_size);
        }
    }
    
    void set_noteChosen(int i,bool flag)
    {
        note[i].noteGraph.isChosen = flag;
        note[i].accidental.sharp.isChosen = flag;
        note[i].accidental.flat.isChosen = flag;
        note[i].accidental.natural.isChosen = flag;
    }
    
    void mouseDown(const juce::MouseEvent &event)override
    {
        
        for(int i=0;i<4;i++)
        {
            set_noteChosen(i,false);
            oppo_staff->set_noteChosen(i, false);
        }
        repaint();
        oppo_staff->repaint();
        if(noteChosen >= 0)
        {
            if(sf==staff_now)set_noteChosen(nt,true);
            else oppo_staff->set_noteChosen(nt,true);
        }
        repaint();
        oppo_staff->repaint();
    }

    int pos[4] = {20,15,9,5};
    int staff_now;
    
    noteComponent note[4];
    
    tone_textComponent tone_text[4] = {tone_textComponent(tone[20][3]),tone_textComponent(tone[15][3]),tone_textComponent(tone[9][3]),tone_textComponent(tone[5][3])};
    
    check_zoneComponent check_zone[4] = {check_zoneComponent(&note[0],this,staff_now,0),check_zoneComponent(&note[1],this,staff_now,1),check_zoneComponent(&note[2],this,staff_now,2),check_zoneComponent(&note[3],this,staff_now,3)};
    
    release_zoneComponent release_zone;
    
    sharpComponent sharpSign[7][2];
    flatComponent flatSign[7][2];
    
private:
    std::unique_ptr<juce::Drawable> staff = juce::Drawable::createFromImageData(BinaryData::Grand_staff_svg, BinaryData::Grand_staff_svgSize);
    staffComponent *oppo_staff;

};

class tonality_zoneComponent : public juce::Component
{
public:
    tonality_zoneComponent(MouseListener *Par,staffComponent *sf1,staffComponent *sf2)
    {
        staff1 = sf1;
        staff2 = sf2;
        Parent = Par;
        addMouseListener(Parent, false);
    }
    ~tonality_zoneComponent(){}
    
    void paint(juce::Graphics &g)override
    {

    }
    

    
    void mouseDown(const juce::MouseEvent &event)override
    {
        if(event.mods.isLeftButtonDown())tonality = std::min(tonality+1,7);
        else if(event.mods.isRightButtonDown())tonality = std::max(tonality-1,-7);
        
        get_tones_now();

        
        for(int i=0;i<7;i++)for(int j=0;j<2;j++)
        {
            staff1->sharpSign[i][j].setVisible(false);
            staff2->sharpSign[i][j].setVisible(false);
            staff1->flatSign[i][j].setVisible(false);
            staff2->flatSign[i][j].setVisible(false);
        }
        
        if(tonality == 0)return;
        
        if(tonality>0)
        {
            for(int i=0;i<=tonality-1;i++)for(int j=0;j<2;j++)
            {
                staff1->sharpSign[i][j].setVisible(true);
                staff2->sharpSign[i][j].setVisible(true);
            }
        }
        else if(tonality<0)
        {
            for(int i=0;i<=abs(tonality)-1;i++)for(int j=0;j<2;j++)
            {
                staff1->flatSign[i][j].setVisible(true);
                staff2->flatSign[i][j].setVisible(true);
            }
        }
        
        
    }
private:
    staffComponent *staff1, *staff2;
    MouseListener *Parent;
};


//==============================================================================

class SceneComponent  : public juce::Component
{
public:
    
    SceneComponent() :  text_Consecutive5ths("Consecutive 5ths"),
                       text_ConsecutiveOct("Consecutive Oct."),
                       text_HiddenConsecutives("Hidden Consec."),
                       text_Overlap("Overlap"),
                       text_Parallel("Parallel")
    {
        
        for(int i=0;i<26;i++)
        {
            tone[i][1]=tone_in_C[i];
            tone[i][3]=tone_in_C[i];
            tone[i][0]=tone_in_C[i]-1;
            tone[i][2]=tone_in_C[i]+1;
        }
        
        setWantsKeyboardFocus(true);
        
        addAndMakeVisible(staff[0]);
        addAndMakeVisible(staff[1]);
        addAndMakeVisible(text_Consecutive5ths);
        addAndMakeVisible(text_ConsecutiveOct);
        addAndMakeVisible(text_HiddenConsecutives);
        addAndMakeVisible(text_Overlap);
        addAndMakeVisible(text_Parallel);
        
        for(int i=0;i<4;i++)
        {
            addAndMakeVisible(tonality_zone[i]);
            tonality_zone[i].toFront(false);
        }
        
       

    }

    ~SceneComponent() override{}

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::lightyellow);
        
        g.setFont(40.0f);
        g.drawText("Natsuki's Four-Part Harmony!", 0, 50, 900, 40, juce::Justification::centred);
    }

    void resized() override
    {
        staff[0].setBounds(50,75,450,350);
        staff[1].setBounds(450,75,450,350);
    
        
        text_Consecutive5ths.setBounds(50, 450, 150, 200);
        text_ConsecutiveOct.setBounds(240, 450, 150, 200);
        text_HiddenConsecutives.setBounds(425, 450, 150, 200);
        text_Overlap.setBounds(585, 450, 125, 200);
        text_Parallel.setBounds(700, 450, 150, 200);
        
        tonality_zone[0].setBounds(90, 125, 50, 118);
        tonality_zone[1].setBounds(90, 295, 55, 62);
        tonality_zone[2].setBounds(490, 125, 50, 118);
        tonality_zone[3].setBounds(490, 295, 55, 62);
    }
    
    void show_flat(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 0;
        staff[sf].note[nt].accidental.sharp.setVisible(false);
        staff[sf].note[nt].accidental.natural.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(true);
        return;
    }
    
    void show_natural(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 1;
        staff[sf].note[nt].accidental.sharp.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(false);
        staff[sf].note[nt].accidental.natural.setVisible(true);
        return;
    }
    
    void show_sharp(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 2;
        staff[sf].note[nt].accidental.natural.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(false);
        staff[sf].note[nt].accidental.sharp.setVisible(true);
        return;
    }
    
    void hide_any_symbol(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 3;
        staff[sf].note[nt].accidental.natural.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(false);
        staff[sf].note[nt].accidental.sharp.setVisible(false);
        return;
    }
    
    void draw_tone_text()
    {
        for(int i=0;i<2;i++)for(int j=0;j<4;j++)
        {
            staff[i].tone_text[j].toneToShow = tone[staff[i].pos[j]][staff[i].note[j].accidentalFlag];
            staff[i].tone_text[j].repaint(staff[i].tone_text[j].getLocalBounds());
        }
    }
    
    int calculate_the_highest(int sf,int nt)
    {
        switch(nt)
        {
            case 0: return 25;
            case 1: return staff[sf].pos[0];
            case 2: return 12;
            case 3: return staff[sf].pos[2];
        }
        return -1;
    }
    
    int calculate_the_lowest(int sf,int nt)
    {
        switch(nt)
        {
            case 0: return staff[sf].pos[1];
            case 1: return 13;
            case 2: return staff[sf].pos[3];
            case 3: return 0;
        }
        return -1;
    }
    
    int calculate_the_dis(int sf,int nt)
    {
        if(nt<=1) return staff[sf].pos[0]-staff[sf].pos[1];
        else return staff[sf].pos[2]-staff[sf].pos[3];
    }
    
    void set_note(int sf,int nt,int x)
    {
        x+=40;
        staff[sf].note[nt].setBounds(x,CoordY[staff[sf].pos[nt]],3*(int)note_size,2*note_size-5);
        staff[sf].check_zone[nt].setBounds(x+35,CoordY[staff[sf].pos[nt]]+14,note_size,note_size);
        
    }
    
    void release_the_note()
    {
        if(noteChosen<0)return;
        noteChosen=-1;
        staff[sf].note[nt].noteGraph.isChosen = false;
        staff[sf].note[nt].accidental.sharp.isChosen = false;
        staff[sf].note[nt].accidental.flat.isChosen = false;
        staff[sf].note[nt].accidental.natural.isChosen = false;
        staff[sf].note[nt].repaint();
    }
    
    
    void set_symbol(int sf,int nt,int x)
    {
        staff[sf].note[nt].accidental.setBounds(x,0,accidental_size+10,accidental_size+10);
    }
    
    void setNoteChosen(int sf,int nt)
    {
        for(int i=0;i<2;i++)for(int j=0;j<4;j++)
        {
            staff[i].note[j].noteGraph.isChosen = ((i==sf&&j==nt) ? true:false);
            staff[i].note[j].accidental.flat.isChosen = ((i==sf&&j==nt) ? true:false);
            staff[i].note[j].accidental.sharp.isChosen = ((i==sf&&j==nt) ? true:false);
            staff[i].note[j].accidental.natural.isChosen = ((i==sf&&j==nt) ? true:false);
        }
        repaint();
    }
    
    void setNoteMarked(int sf,int nt,bool flag)
    {
            staff[sf].note[nt].noteGraph.isMarked = flag;
            staff[sf].note[nt].accidental.flat.isMarked = flag;
            staff[sf].note[nt].accidental.sharp.isMarked = flag;
            staff[sf].note[nt].accidental.natural.isMarked = flag;
        repaint();
    }
    
    //分类讨论的神
    void shift(int sf,int up,int down)
    {
        int dis = calculate_the_dis(sf,up);
        bool symbolUp = (staff[sf].note[up].accidentalFlag==3 ? false : true);
        bool symbolDown = (staff[sf].note[down].accidentalFlag==3 ? false : true);
        
        if(!symbolUp)
        {
            switch(dis)
            {
                case 0:
                    set_note(sf,down,161);
                    set_symbol(sf,down,10);
                    return;
                case 1:
                    set_note(sf,down,169);
                    set_symbol(sf,down,10);
                    return;
                default:
                    set_note(sf,down,185);
                    set_symbol(sf,down,10);
                    return;
            }
        }
        else if(symbolUp && (!symbolDown))
        {
            switch(dis)
            {
                case 0:
                    set_note(sf,down,142);
                    set_symbol(sf, up, 10);
                    return;
                case 1:
                    set_note(sf,down,169);
                    set_symbol(sf, up, -5);
                    set_symbol(sf,down,0);
                    return;
                default:
                    set_note(sf,down,185);
                    set_symbol(sf,up, 10);
                    return;
            }
        }
        else
        {
            switch(dis)
            {
                case 0:
                    set_note(sf,down,142);
                    set_symbol(sf, up, 10);
                    set_symbol(sf, down, 10);
                    return;
                case 1:
                    set_note(sf,down,169);
                    set_symbol(sf, up, -5);
                    set_symbol(sf, down, -8);
                    return;
                case 2:
                    set_note(sf,down,185);
                    set_symbol(sf, up, 10);
                    set_symbol(sf, down, -5);
                    return;
                case 3:
                    set_note(sf,down,185);
                    set_symbol(sf, up, 10);
                    set_symbol(sf, down, 0);
                    return;
                case 4:
                    set_note(sf,down,185);
                    set_symbol(sf, up, 10);
                    set_symbol(sf, down, 5);
                    return;
                default:
                    set_note(sf,down,185);
                    set_symbol(sf, up, 10);
                    set_symbol(sf, down, 10);
                    return;
            }
        }
       
    }
    
    void renewal()
    {
        //描画音符
        set_note(sf,nt,185);
        
        //偏移
        if(nt<=1)shift(sf,0,1);
        else shift(sf,2,3);
        
   
        //描画加线
        
        if(staff[sf].pos[nt]==0||staff[sf].pos[nt]==12||staff[sf].pos[nt]==13||staff[sf].pos[nt]==25)
        {
            int nt1 = nt, nt2 = 1-(nt%2)+(nt/2)*2;
            int nt_min = std::min(nt1,nt2);
            if(staff[sf].pos[nt1]==staff[sf].pos[nt2]&&staff[sf].note[nt_min].accidentalFlag==3)
            {
                staff[sf].note[nt_min].line.startX = 10.0f;
            }
            else
            {
                staff[sf].note[std::min(nt1,nt2)].line.startX = 2.0f;
            }
                staff[sf].note[nt].line.setVisible(true);
        }
        else staff[sf].note[nt].line.setVisible(false);
        
        //更新文本
        draw_tone_text();
        
        //判定
        int tone_now[2][4];
        for(int i=0;i<2;i++)for(int j=0;j<4;j++)
        {
            tone_now[i][j] = tone[staff[i].pos[j]][staff[i].note[j].accidentalFlag];
        }
        
        
        marked_note.clear();
        //四部同向
        text_Parallel.Opa = (isParallel(tone_now,marked_note)? 1.0f : 0.3f);
        text_Parallel.repaint();
        
        //声部交叉
        text_Overlap.Opa = (isOverlap(tone_now,marked_note)? 1.0f : 0.3f);
        text_Overlap.repaint();
        
        //隐伏五八
        text_HiddenConsecutives.Opa = (isHiddenConsec(tone_now,marked_note)? 1.0f : 0.3f);
        text_HiddenConsecutives.repaint();
        
        //平行五度
        text_Consecutive5ths.Opa = (isConsecutive5ths(tone_now,marked_note)? 1.0f : 0.3f);
        text_Consecutive5ths.repaint();
        
        //平行八度
        text_ConsecutiveOct.Opa = (isConsecutiveOct(tone_now,marked_note)? 1.0f : 0.3f);
        text_ConsecutiveOct.repaint();
        
        for(int i=0;i<2;i++)for(int j=0;j<4;j++)setNoteMarked(i,j,false);
        for(auto note_marked : marked_note)setNoteMarked(note_marked.first, note_marked.second,true);
        
        return;
    }
    
    bool keyPressed(const juce::KeyPress& key) override
    {
        if(noteChosen<0) return true;
        //按条件处理
        if(key.getKeyCode()==key.rightKey)noteChosen = noteChosen%4+4;
        if(key.getKeyCode()==key.leftKey)noteChosen = noteChosen%4;
        if(key.getKeyCode()==key.upKey)noteChosen = std::max(0,noteChosen-1);
        if(key.getKeyCode()==key.downKey)noteChosen = std::min(7,noteChosen+1);
        sf = noteChosen/4; nt = noteChosen%4;

        setNoteChosen(sf,nt);
        
        if(key.getKeyCode()==90)show_flat(sf, nt); //按下z键降号
        if(key.getKeyCode()==88)show_natural(sf, nt); //按下x键还原号
        if(key.getKeyCode()==67)show_sharp(sf, nt);//按下c键升号
        if(key.getKeyCode()==86)hide_any_symbol(sf, nt);//按下v键消除临时变音记号
    
        //更新垂直方向位置
        if(key.getKeyCode()==87)
        {
            staff[sf].pos[nt] = std::min(staff[sf].pos[nt]+1,calculate_the_highest(sf, nt));
        }
        else if(key.getKeyCode()==83)
        {
            staff[sf].pos[nt] = std::max(staff[sf].pos[nt]-1,calculate_the_lowest(sf, nt));
        }
        
        //刷新画面
        renewal();

        return true;
    }
    
    void mouseDown(const juce::MouseEvent &event)override
    {
        renewal();
    }

    
private:
    staffComponent staff[2] = {staffComponent(0,&staff[1]),staffComponent(1,&staff[0])};
    check_textComponent text_Consecutive5ths;
    check_textComponent text_ConsecutiveOct;
    check_textComponent text_HiddenConsecutives;
    check_textComponent text_Overlap;
    check_textComponent text_Parallel;
    tonality_zoneComponent tonality_zone[4] = {tonality_zoneComponent(this,&staff[0],&staff[1]),tonality_zoneComponent(this,&staff[0],&staff[1]),tonality_zoneComponent(this,&staff[0],&staff[1]),tonality_zoneComponent(this,&staff[0],&staff[1])};
    
   

};

class MainComponent : public juce::Component
{
public:
    MainComponent()
    {
        addAndMakeVisible(scene1);
        setSize(900,600);
    }
    ~MainComponent(){}
    
    void paint(juce::Graphics &g)override
    {
       
    }
    
    void resized()override
    {
        scene1.setBounds(getLocalBounds());
    }
private:
    SceneComponent scene1;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
    




