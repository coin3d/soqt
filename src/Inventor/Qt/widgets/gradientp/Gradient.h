#ifndef GRADIENT_H
#define GRADIENT_H

#include <Inventor/SbColor4f.h>
#include <Inventor/lists/SbList.h>
#include <Inventor/system/inttypes.h>
#include <Inventor/SbString.h>

class SbColor4f;
class QColor;

class Tick {
public:
  SbColor4f left;
  SbColor4f right;
  float t;
};

class Gradient
{
public:
  Gradient(SbColor4f * color0 = NULL, SbColor4f * color1 = NULL);
  Gradient(const Gradient& grad);
  Gradient(const SbString filename);
  ~Gradient();

  int numTicks() const;
  float getParameter(int i) const;
  SbColor4f eval(float t) const;
  
  void moveTick(int i, float t);
  void removeTick(int i);
  int insertTick(float t);

  const SbList<Tick> & getTicks(void) const;

  void setChangeCallback(void (*changeCB)(void));

  uint32_t getColor(int i, SbBool left) const;
  void setColor(int i, SbBool left, const SbColor4f &);

  void getColorArray(SbColor4f * colors, int num) const;

  void save(const SbString& filename);
  void load(const SbString& filename);

  Gradient & operator = (const Gradient & grad);

private:
  SbList<Tick> ticks;
  void (*changeCB)(void);
};




#endif // GRADIENT_H