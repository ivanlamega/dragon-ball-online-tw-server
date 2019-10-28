CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 280;
	title = 28002;

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
				idx0 = 3211103;
				cnt0 = 15;
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
			stdiag = 28007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4511202;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
			}
			CDboTSCheckClrQst
			{
				and = "269;";
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
				conv = 28009;
				ctype = 1;
				idx = 4511202;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 28008;
				gtype = 2;
				area = 28001;
				goal = 28004;
				m0fz = "-2784.000000";
				m0widx = 1;
				sort = 28005;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4941.000000";
				m0ttip = 28015;
				rwd = 100;
				taid = 1;
				title = 28002;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 3211103;
				cnt0 = 9;
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
			cont = 28008;
			gtype = 2;
			oklnk = 2;
			area = 28001;
			goal = 28004;
			sort = 28005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 28002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 28014;
			nextlnk = 101;
			rwdtbl = 28001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511202;
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

