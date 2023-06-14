#pragma once
#include <JuceHeader.h>
const float note_size = 25.0f;
const float accidental_size = 39.0f;



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
