CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1102;
	title = 110202;

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
				conv = 110209;
				ctype = 1;
				idx = 4072118;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 110208;
				gtype = 1;
				area = 110201;
				goal = 110204;
				grade = 132203;
				rwd = 100;
				sort = 110205;
				stype = 2;
				taid = 1;
				title = 110202;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 110214;
			nextlnk = 254;
			rwdtbl = 110201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061102;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 110208;
			gtype = 1;
			oklnk = 2;
			area = 110201;
			goal = 110204;
			sort = 110205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 110202;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 110207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4072118;
			}
			CDboTSCheckLvl
			{
				maxlvl = 50;
				minlvl = 42;
			}
			CDboTSCheckClrQst
			{
				and = "1096;";
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
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

