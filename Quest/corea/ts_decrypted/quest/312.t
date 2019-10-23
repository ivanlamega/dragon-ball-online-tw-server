CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 312;
	title = 31202;

	CNtlTSGroup
	{
		gid = 0;

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
				idx0 = 1512103;
				cnt0 = 20;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 31207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511602;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 24;
				minlvl = 16;
			}
			CDboTSCheckClrQst
			{
				and = "311;";
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
				conv = 31209;
				ctype = 1;
				idx = 4511602;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 31208;
				gtype = 2;
				area = 31201;
				goal = 31204;
				m0fz = "-1906.000000";
				m0widx = 1;
				sort = 31205;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "5006.000000";
				m0ttip = 31215;
				rwd = 100;
				taid = 1;
				title = 31202;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 1512103;
				cnt0 = 16;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 31208;
			gtype = 2;
			oklnk = 2;
			area = 31201;
			goal = 31204;
			sort = 31205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 31202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 31214;
			nextlnk = 101;
			rwdtbl = 31201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511602;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
}

