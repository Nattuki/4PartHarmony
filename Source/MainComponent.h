#pragma once

#include <JuceHeader.h>

const int CoordY[26] = {281,273,265,256,248,239,231,223,214,206,198,189,182,129,122,114,105,97,88,80,72,63,55,47,38,31};
const int tone_abs[26] = {16,17,19,21,23,24,26,28,29,31,33,35,36,36,38,40,41,43,45,47,48,50,52,53,55,57};
int tone[26][4];
const float note_size = 25.0f;
const float accidental_size = 39.0f;
const float staff_size = 350.0f;




//==============================================================================

class textComponent : public juce::Component
{
public:
    textComponent(int startTone) : toneToShow(startTone)
    {}
    ~textComponent(){}
    
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

class noteGraphComponent : public juce::Component
{
public:
    noteGraphComponent(){}
    ~noteGraphComponent(){}
    
    void paint(juce::Graphics &g) override
    {
        nature->drawWithin(g, juce::Rectangle<float>(note_size,note_size), juce::RectanglePlacement::Flags::centred, 1.0f);
    }
    
    void resized() override
    {}
    
    
private:
    std::unique_ptr<juce::Drawable>nature = juce::Drawable::createFromImageData(BinaryData::note_svg,BinaryData::note_svgSize);
};



class natureComponent : public juce::Component
{
public:
    natureComponent(){}
    ~natureComponent(){}
    
    void paint(juce::Graphics &g) override
    {
        nature->drawWithin(g, juce::Rectangle<float>(accidental_size,accidental_size), juce::RectanglePlacement::Flags::centred, 1.0f);
    }
    
    void resized() override
    {}
    
    
private:
    std::unique_ptr<juce::Drawable>nature = juce::Drawable::createFromImageData(BinaryData::nature_svg,BinaryData::nature_svgSize);
};

class flatComponent : public juce::Component
{
public:
    flatComponent(){}
    ~flatComponent(){}
    
    void paint(juce::Graphics &g) override
    {
        nature->drawWithin(g, juce::Rectangle<float>(accidental_size,accidental_size), juce::RectanglePlacement::Flags::centred, 1.0f);
    }
    
    void resized() override
    {}
    
private:
    std::unique_ptr<juce::Drawable>nature = juce::Drawable::createFromImageData(BinaryData::flat_svg,BinaryData::flat_svgSize);
};

class sharpComponent : public juce::Component
{
public:
    sharpComponent(){}
    ~sharpComponent(){}
    
    void paint(juce::Graphics& g) override
    {
        note->drawWithin(g, juce::Rectangle<float>(accidental_size,accidental_size), juce::RectanglePlacement::Flags::centred, 1.0f);
    }
    
    void resized() override
    {
        
    }
private:
    std::unique_ptr<juce::Drawable>note = juce::Drawable::createFromImageData(BinaryData::sharp_svg, BinaryData::sharp_svgSize);
};

class accidentalComponent: public juce::Component
{
public:
    accidentalComponent()
    {
        addChildComponent(flat);
        addChildComponent(sharp);
        addChildComponent(nature);
    }
    ~accidentalComponent(){}
    
    void paint(juce::Graphics &g) override
    {
        
    }
    
    void resized() override
    {
        nature.setBounds(0, 7,accidental_size,accidental_size);
        sharp.setBounds(-2, 7,accidental_size,accidental_size);
        flat.setBounds(-2,-2,accidental_size,accidental_size);
    }
    
    natureComponent nature;
    sharpComponent sharp;
    flatComponent flat;
};

class lineComponent : public juce::Component
{
public:
    lineComponent(){}
    ~lineComponent(){}
    
    void paint(juce:: Graphics &g) override
    {
        g.setColour(juce::Colours::black);
        g.drawLine(2,12,40,12,3);
    }
    
    void resized() override
    {}
private:
};


class noteComponent : public juce::Component
{
public:
    noteComponent()
    {
        addAndMakeVisible(note);
        addAndMakeVisible(accidental);
        addChildComponent(line);
    }
    ~noteComponent(){}
    
    void paint(juce::Graphics& g) override
    {
    }
    
    void resized() override
    {
        note.setBounds(35,14,note_size,note_size);
        accidental.setBounds(10,0,accidental_size+10,accidental_size+10);
        line.setBounds(26,14,50,50);
    }
    
    int accidentalFlag = 3;
    
    accidentalComponent accidental;
    noteGraphComponent note;
    lineComponent line;
private:
    
};

//==============================================================================

class staffComponent : public juce::Component
{
public:
    
    staffComponent()
    {
        for(int i=0;i<4;i++)
        {
            addAndMakeVisible(note[i]);
            addAndMakeVisible(text[i]);
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
            note[i].setBounds(185,CoordY[pos[i]],3*(int)note_size,2*accidental_size);
            text[i].setBounds(30,320+i*25,50,50);
        }
            
    }
    
    int pos[4] = {20,15,9,5};
    
    noteComponent note[4];
    textComponent text[4] = {textComponent(48),textComponent(40),textComponent(31),textComponent(24)};
    

private:
    std::unique_ptr<juce::Drawable> staff = juce::Drawable::createFromImageData(BinaryData::Grand_staff_svg, BinaryData::Grand_staff_svgSize);

};

//==============================================================================

class MainComponent  : public juce::Component
{
public:
    
    MainComponent()
    {
        for(int i=0;i<26;i++)
        {
            tone[i][1]=tone_abs[i];
            tone[i][3]=tone_abs[i];
            tone[i][0]=tone_abs[i]-1;
            tone[i][2]=tone_abs[i]+1;
            
        }
        
        setSize (900, 600);
        setWantsKeyboardFocus(true);
        addAndMakeVisible(staff[0]);
        addAndMakeVisible(staff[1]);
    }

    ~MainComponent() override{}

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::lightyellow);
        
    }

    void resized() override
    {
        staff[0].setBounds(50,50,350,450);
        staff[1].setBounds(500,50,350,450);
    }
    
    void show_flat(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 0;
        staff[sf].note[nt].accidental.sharp.setVisible(false);
        staff[sf].note[nt].accidental.nature.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(true);
        return;
    }
    
    void show_natural(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 1;
        staff[sf].note[nt].accidental.sharp.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(false);
        staff[sf].note[nt].accidental.nature.setVisible(true);
        return;
    }
    
    void show_sharp(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 2;
        staff[sf].note[nt].accidental.nature.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(false);
        staff[sf].note[nt].accidental.sharp.setVisible(true);
        return;
    }
    
    void hide_any_symbol(int sf,int nt)
    {
        staff[sf].note[nt].accidentalFlag = 3;
        staff[sf].note[nt].accidental.nature.setVisible(false);
        staff[sf].note[nt].accidental.flat.setVisible(false);
        staff[sf].note[nt].accidental.sharp.setVisible(false);
        return;
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
        staff[sf].note[nt].setBounds(x,CoordY[staff[sf].pos[nt]],3*(int)note_size,(int)accidental_size+9);
    }
    
    void set_symbol(int sf,int nt,int x)
    {
        staff[sf].note[nt].accidental.setBounds(x,0,accidental_size+10,accidental_size+10);
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

    int noteChosen = 0;
    int sf,nt;
    bool keyPressed(const juce::KeyPress& key) override
    {
        //按条件处理
        if(key.getKeyCode()==key.rightKey)noteChosen = noteChosen%4+4;
        if(key.getKeyCode()==key.leftKey)noteChosen = noteChosen%4;
        if(key.getKeyCode()==key.upKey)noteChosen = std::max(0,noteChosen-1);
        if(key.getKeyCode()==key.downKey)noteChosen = std::min(7,noteChosen+1);
        sf = noteChosen/4; nt = noteChosen%4;

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
        
        //描画音符
        set_note(sf,nt,185);
        
        //偏移
        if(nt<=1)shift(sf,0,1);
        else shift(sf,2,3);
        
   
        //描画加线
        if(staff[sf].pos[nt]==0||staff[sf].pos[nt]==12||staff[sf].pos[nt]==13||staff[sf].pos[nt]==25)staff[sf].note[nt].line.setVisible(true);
        else staff[sf].note[nt].line.setVisible(false);
        
        //更新文本
        staff[sf].text[nt].toneToShow = tone[staff[sf].pos[nt]][staff[sf].note[nt].accidentalFlag];
        
        //描画文本
        staff[sf].text[nt].repaint(staff[sf].text[nt].getLocalBounds());
        
        
        return true;
    }
    

private:
    staffComponent staff[2];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};





