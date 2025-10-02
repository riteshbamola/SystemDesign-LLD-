//Document Editor System Design

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;


//abstract class for document Element
class DocumentElement{
    public:
    virtual string render()=0;
};
 //Concrete classes for document Element
class TextElement: public DocumentElement{
    private:
    string text;
    public:
    TextElement(string text){
        this->text=text;
    }
    string render() override {
        return text;
    }
};
class ImageElement: public DocumentElement{
    private:
    string path;
    public:
    ImageElement(string path){
        this->path=path;
    }
    string render() override {
        
        return "[Image :"+path+"]";
    }
};
class NewLineElement: public DocumentElement{
    public:
    string render() override{
        return "\n";
    }
};

class NewTabElement: public DocumentElement{
    public:
    string render() override{
        return "\t";
    }
};

// class for Document holding collection of elements

class Document{
    private:
    vector<DocumentElement*>elements;
    public:
    void addElement(DocumentElement *element){
        elements.push_back(element);
    }

    string render(){
        string result;
        for(auto el: elements){
            result +=el->render();
        }
        return result;
    }
};


//Persistence Interface
class Persistance{
    public:
    virtual void save(string data)=0;
};
class FileSave: public Persistance{
    public:
    void save(string data) override{
        ofstream outfile("Document.txt");
        if(outfile){
            outfile<<data;
            outfile.close();
            cout<<"Document Saved in File Succesfully"<<endl;
        }
        else{
             cout<<"Error: Unable to open File"<<endl;
        }
    }
};
class DBSave: public Persistance{
    public:
    void save (string data) override{
        //save to DB;
    }
};


//Document Editor managing client interactions

class DocumentEditor{

    private:
        Document* document;
        Persistance * storage;
        string renderedDocument;
    
    public:
        DocumentEditor(Document* document, Persistance *storage)
        {
            this->document= document;
            this->storage=storage;
        }
        void addText(string text)
        {
            document->addElement(new TextElement(text));
        }

        void addImage(string path){
            document->addElement(new ImageElement(path));
        }

        void addnewLine(){
            document->addElement(new NewLineElement());
        }
        void addTab(){
            document->addElement(new NewTabElement());
        }

        string render(){
            if(renderedDocument.empty())
                renderedDocument=document->render();
            return renderedDocument;
        }

        void saveDocument(){
            storage->save(renderedDocument);
        }


};

int main(){
    Document *doc = new Document();
    Persistance *storage= new FileSave();

    DocumentEditor *editor = new DocumentEditor(doc,storage);

    editor->addText("Hello World");
    editor->addnewLine();
    editor->addImage("C:/Desktop/Ritesh/image.jpg");
    editor->addTab();
    editor->addText("this is a document Editor");

    cout<<editor->render();
    cout<<endl;
    editor->saveDocument();

}