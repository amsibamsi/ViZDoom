#include "ViziaDoomGamePython.h"

namespace Vizia {

    using boost::python::tuple;
    using boost::python::api::object;

#define PY_NONE object()

    DoomGamePython::DoomGamePython() {
        Py_Initialize();
        import_array();
        /* Numpy arrays won't work unless this strnage function is envoked.*/
        boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
        //boost::numpy::initialize();
        this->numpyImage = NULL;
        this->numpyVars = NULL;
    }
    DoomGamePython::~DoomGamePython() {
        delete this->numpyImage;
        delete this->numpyVars;
        this->numpyImage = NULL;
        this->numpyVars = NULL;
    }

    bool DoomGamePython::init() {
        bool initSuccess = DoomGame::init();

        if (initSuccess) {

            int channels = this->getScreenChannels();
            int x = this->getScreenWidth();
            int y = this->getScreenHeight();
            npy_intp imageShape[3];
            switch(this->getScreenFormat())
            {
                case CRCGCB:
                case CRCGCBCA:
                case CBCGCR:
                case CBCGCRCA:
                    imageShape[0] = channels;
                    imageShape[1] = x;
                    imageShape[2] = y;
                    break;
                default:
                    imageShape[0] = x;
                    imageShape[1] = y;
                    imageShape[2] = channels;
            }
            PyObject *img = PyArray_SimpleNewFromData(3, imageShape, NPY_UBYTE, this->state.imageBuffer);
            boost::python::handle<> handle(img);
            this->numpyImage = (boost::python::numeric::array*)(new boost::python::object(handle));
            if (this->state.vars.size() > 0) {
                npy_intp varLen = this->state.vars.size();
                PyObject *vars = PyArray_SimpleNewFromData(1, &varLen, NPY_INT32, this->state.vars.data());
                boost::python::handle<> handle(vars);
                this->numpyVars = (boost::python::numeric::array*)(new boost::python::numeric::array(handle));

            }
        }
        return initSuccess;
    }

    float DoomGamePython::makeAction(boost::python::list actionList) {
        // TODO what if isFinished()?
        int listLength = boost::python::len(actionList);
        std::vector<bool> action = std::vector<bool>(listLength);
        for (int i = 0; i < listLength; i++) {
            action[i] = boost::python::extract<bool>(actionList[i]);
        }
        return DoomGame::makeAction(action);
    }

    object DoomGamePython::getState() {
        if (isEpisodeFinished()) {
            return PY_NONE;
        }
        if (state.vars.size() > 0) {
            return boost::python::make_tuple(this->state.number, this->numpyImage->copy(), this->numpyVars->copy());
        }
        else {
            return boost::python::make_tuple(this->state.number, this->numpyImage->copy());
        }

    }

/* not sure if we need this */
    object DoomGamePython::getLastAction() {
        //TODO
        return PY_NONE;
    }
}