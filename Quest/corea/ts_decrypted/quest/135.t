CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 135;
	title = 13502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 13509;
				ctype = 1;
				idx = 4072122;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 13508;
				gtype = 1;
				area = 13501;
				goal = 13504;
				grade = 132203;
				rwd = 100;
				sort = 13505;
				stype = 2;
				taid = 1;
				title = 13502;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 13508;
			gtype = 1;
			oklnk = 2;
			area = 13501;
			goal = 13504;
			sort = 13505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 13502;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
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
			desc = 13514;
			nextlnk = 254;
			rwdtbl = 13501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 13507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 4072122;
			}
			CDboTSCheckPCCls
			{
				clsflg = 3;
			}
			CDboTSCheckLvl
			{
				maxlvl = 25;
				minlvl = 17;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

