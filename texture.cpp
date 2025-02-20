#include "texture.h"
#include <string>
#include "shader.h"
#include <GL/glew.h>
#include "stb_image.h"
#include <assert.h>
#include "error.h"
#include <vector>
GLuint texture;
int num_textures;
const int reqcomponents = 4;
int getNumTextures(){
    return num_textures;
}
void genTexture(std::vector<std::string> filename)
{
    glError = glGetError();
    num_textures = filename.size();
    printf("num_textures = %i\n", num_textures);
    int width=0;
    int height=0;
    int numcomponents=0;
    glGenTextures(1, &texture);
    unsigned char *imagedata = nullptr;
    int imagedata_len = 0;
    unsigned char *temp_imagedata;
    for (int i = 0; i < num_textures; i++)
    {
        printf("working on texture: %i\n",i);
        int tempHeight;
        temp_imagedata = stbi_load(filename[i].c_str(), &width,
                                             &tempHeight, &numcomponents, reqcomponents);
        if (temp_imagedata == NULL)
        {
            printf("can not find texture %s\n", filename[i].c_str());
        }
        
        printf("temp height: %i widthL %i\n",tempHeight,width);
        if(numcomponents<reqcomponents){
            numcomponents=reqcomponents;
        }
        int tempLen = numcomponents*tempHeight*width;
        //printf("image_data address: %p\n",(void*)imagedata);
        
        if(i==0){
           imagedata = (unsigned char*) calloc(tempLen,sizeof(unsigned char));
        }else{
            imagedata=(unsigned char*) realloc(imagedata,sizeof(char)*(imagedata_len+tempLen));
        }
       
        printf("image_data allocated: %p\n",(void*)imagedata);
        memcpy(imagedata+imagedata_len,temp_imagedata,tempLen);
        /*
        for(int i =0; i<tempLen;i++){
            imagedata[imagedata_len+i]=temp_imagedata[i];
        }
        */
        imagedata_len+=tempLen;
        height+=tempHeight;
        free(temp_imagedata);
    }
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, imagedata);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //stbi_image_free(imagedata);
        glError= glGetError();
        free(imagedata);
        if (glError != 0)
        {
            printf("glError %i\n", glError);
        }
    
}

void delTexture()
{
    for (int i = 0; i < num_textures; i++)
    {
        glDeleteTextures(1, &texture);
    }
}
void bindTexture(unsigned int unit)
{
    glActiveTexture(GL_TEXTURE0 + 0);
    glError= glGetError();
    glBindTexture(GL_TEXTURE_2D, texture);
    glError= glGetError();
    setTexture(0);
    //printf("unit = %i",unit);
    //assert(unit >= 0 && unit <= 31);
    /*
    glActiveTexture(GL_TEXTURE0 + unit);
    glError= glGetError();
    glBindTexture(GL_TEXTURE_2D, texture[unit]);
    glError= glGetError();
    setTexture(unit);
    glError= glGetError();
    if (glError != 0)
    {
        printf("glError %i\n", glError);
    }
    */
}