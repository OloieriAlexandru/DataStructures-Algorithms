#ifndef TRIE_H
#define TRIE_H

// https://infoarena.ro/job_detail/2453996?action=view-source

class trie
{
private:
#define uint unsigned int
#define endWord(w) (!(*w))
    static const uint alphabetSize = 26;
    class trieNode
    {
    private:
        int cnt = 0, oth = 0;
        trieNode *f[alphabetSize] = {};
    public:
        void ins(char *c)
        {
            if (endWord(c))
            {
                ++cnt;
                return;
            }
            if (!f[*c - 'a'])
            {
                f[*c - 'a'] = new trieNode;
                ++oth;
            }
            f[*c - 'a']->ins(c+1);
        }
        int getCnt(char *c)
        {
            if (endWord(c))
                return cnt;
            if (!f[*c - 'a'])
                return 0;
            return f[*c-'a']->getCnt(c+1);
        }
        bool rem(char *c)
        {
            if (endWord(c))
            {
                --cnt;
                if (!cnt && !oth) return true;
                return false;
            }
            if (f[*c-'a']->rem(c+1))
            {
                delete f[*c-'a'];
                f[*c-'a'] = 0;
                --oth;
                if (!cnt && !oth) return true;
            }
            return false;
        }
        int largestPref(char *c)
        {
            if (endWord(c) || !f[*c-'a'])
                return 0;
            return 1 + f[*c-'a']->largestPref(c+1);
        }
        void remAll()
        {
            if (!oth && !cnt)
                return;
            for (uint tr = 0; tr < alphabetSize; ++tr)
            {
                if (!f[tr])
                    continue;
                f[tr]->remAll();
            }
        }
    };
public:
    trieNode *root;
    trie()
    {
        root = new trieNode;
    }
    void addWordApp(char *w)
    {
        root->ins(w);
    }
    int countWordApp(char *w)
    {
        return root->getCnt(w);
    }
    void removeWordApp(char *w)
    {
        root->rem(w);
    }
    int getLargestWordPref(char *w)
    {
        return root->largestPref(w);
    }
    void clearTrie()
    {
        root->remAll();
    }
};

#endif
