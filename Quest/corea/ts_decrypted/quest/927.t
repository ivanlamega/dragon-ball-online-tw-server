CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 927;
	title = 92702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 92708;
			gtype = 3;
			oklnk = 2;
			area = 92701;
			goal = 92704;
			sort = 92705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 92702;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 92707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5041201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 40;
				minlvl = 32;
			}
			CDboTSCheckClrQst
			{
				and = "926;";
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActWorldPlayScript
			{
				sid = 927;
				start = 0;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 92709;
				ctype = 1;
				idx = 5041201;
				taid = 2;
			}
			CDboTSActWorldPlayScript
			{
				sid = 927;
				start = 1;
				taid = 4;
				uof = 1;
			}
			CDboTSActRegQInfo
			{
				cont = 92708;
				gtype = 3;
				area = 92701;
				goal = 92704;
				m0fz = "1345.000000";
				m0widx = 1;
				sort = 92705;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3681.000000";
				m0ttip = 92715;
				rwd = 100;
				taid = 1;
				title = 92702;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 7901101;
				cnt0 = 3;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 92714;
			nextlnk = 101;
			rwdtbl = 92701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142101;
			}
		}
	}
}

