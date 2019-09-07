void Start()
{
Material@ mat = Material();
mat.Save("DefaultMat.xml");
Print("Saved default material to DefaultMat.xml");
engine.Exit();
}
