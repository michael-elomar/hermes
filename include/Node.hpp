#ifndef NODE_HPP
#define NODE_HPP

namespace hermes
{
    class Node
    {
        public:
            Node();
            void setMode(bool mode);
            bool getMode();
        private:
            bool mode;

    };
}
#endif


