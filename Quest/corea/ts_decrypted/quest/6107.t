CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 1;
	tid = 6107;
	title = 610702;

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
				eitype = 4;
				idx0 = -1;
				rate0 = "1.000000";
				cnt0 = 0;
				ectype = -1;
				etype = 1;
				nidx0 = -1;
				taid = 1;
				esctype = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 253;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 610709;
				ctype = 1;
				idx = 2413105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 610708;
				gtype = 1;
				area = 610701;
				goal = 610704;
				grade = 157103;
				rwd = 100;
				sort = 610705;
				stype = 1;
				taid = 1;
				title = 610702;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cd0 = 92022;
				eitype = 4;
				idx0 = 383;
				rate0 = "1.000000";
				cnt0 = 30;
				ectype = 0;
				etype = 0;
				nidx0 = -1;
				taid = 3;
				esctype = 0;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			didx0 = 19007;
			dval0 = 1;
			desc = 610714;
			nextlnk = 101;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 0;

			CDboTSClickNPC
			{
				npcidx = 2413105;
			}
			CDboTSCheckSToCEvt
			{
				itype = 4;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 610708;
			gtype = 1;
			oklnk = 2;
			area = 610701;
			goal = 610704;
			sort = 610705;
			prelnk = "0;";
			ds = 0;
			grade = 157103;
			rwd = 100;
			title = 610702;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "2;1;0;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 610707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 7;
			}
			CDboTSClickNPC
			{
				npcidx = 2413105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 50;
				minlvl = 46;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 383;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
	}
}

